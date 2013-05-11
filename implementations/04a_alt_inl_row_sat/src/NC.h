#ifndef NC_H
#define NC_H

#include "common.h"
#include <cstring>
namespace NC
{

void TransformedDomainBoxFilter(Mat2<float3>& img,
                                Mat2<float3>& sat,
                                Mat2<float> dIdx, float boxR)
{
    assert(img.width == sat.width);
    assert(img.height == sat.height);

    FP_CALL_START(FunP::ID_boxFilter);

    const uint W = img.width;
    const uint H = img.height;

    std::vector<float3> imgRow(W);

    for (uint i=0; i<H; i++)
    {
        uint posL = 0;
        uint posR = 0;

        memcpy(&imgRow[0],&img.data[i*W],sizeof(float3)*W);

        // row sat
        float3 sum; sum.r = sum.g = sum.b = 0;

        for (uint j=0; j<W; j++)
        {
            uint idx = i*W + j;

            // compute box filter bounds
            float dtL = dIdx.data[idx] - boxR;
            float dtR = dIdx.data[idx] + boxR;

            // update box filter window
            while (dIdx.data[i*W+posL] < dtL && posL < W-1)
            {
                sum.r -= imgRow[posL].r;
                sum.g -= imgRow[posL].g;
                sum.b -= imgRow[posL].b;
                posL++;
            }
            while (posR < W && dIdx.data[i*W+posR] < dtR )  // attention, allows for index = W
            {
                sum.r += imgRow[posR].r;
                sum.g += imgRow[posR].g;
                sum.b += imgRow[posR].b;
                posR++;
            }

            // compute box filter value
            uint lIdx = posL;
            uint uIdx = posR;

            // TODO: mult vs. div?
            int delta = uIdx - lIdx;
            float invD = 1.0f / delta;

            img.data[idx].r = sum.r * invD;
            img.data[idx].g = sum.g * invD;
            img.data[idx].b = sum.b * invD;
        }
    }

    FP_CALL_END(FunP::ID_boxFilter);
}


void filter(Mat2<float3>& img, float sigma_s, float sigma_r, uint nIterations)
{
    FP_CALL_START(FunP::ID_ALL);
    // Estimate horizontal and vertical partial derivatives using finite differences.
    FP_CALL_START(FunP::ID_domainTransform);
    Mat2<float3> dIcdx = diffX(img);
    Mat2<float3> dIcdy = diffY(img);

    const uint W = img.width;
    const uint H = img.height;

    // Compute the l1-norm distance of neighbor pixels.
    

    Mat2<float> dIdx(W,H);
    Mat2<float> dIdy(W,H);

    for (uint i=0; i<H; i++)
    {
        dIdx.data[i*W] = 0.0f;
        for (uint j=1; j<W; j++)
        {
            uint idx = i*W + j;
            dIdx.data[idx] = fabs(dIcdx.data[idx-1].r) +
                             fabs(dIcdx.data[idx-1].g) +
                             fabs(dIcdx.data[idx-1].b);
        }
    }

    for (uint j=0; j<W; j++)
    {
        dIdy.data[j] = 0.0f;
    }
    for (uint i=1; i<H; i++)
    {
        for (uint j=0; j<W; j++)
        {
            uint idx = i*W + j;
            dIdy.data[idx] = fabs(dIcdy.data[idx-W].r) +
                             fabs(dIcdy.data[idx-W].g) +
                             fabs(dIcdy.data[idx-W].b);
        }
    }

    // Compute the derivatives of the horizontal and vertical domain transforms.
    float s = sigma_s/sigma_r;
    for (uint i=0; i<H*W; i++)
    {
        dIdx.data[i] = 1.0f + s*dIdx.data[i];
        dIdy.data[i] = 1.0f + s*dIdy.data[i];
    }
    FP_CALL_END(FunP::ID_domainTransform);

    Mat2<float> dIdyT(H,W);

    cumsumX(dIdx);
    transposeB(dIdy,dIdyT);
    cumsumX(dIdyT);

    Mat2<float3> satX(img.width+1,img.height);
    Mat2<float3> satY(img.height+1,img.width);

    Mat2<float3> imgT(img.height,img.width);

    for(uint i=0; i<nIterations; i++)
    {
        // Compute the sigma value for this iteration
        float sigmaHi = sigma_s * sqrt(3) * powf(2.0,(nIterations - (i+1))) / sqrt(powf(4,nIterations)-1);

        // Compute the radius of the box filter with the desired variance.
        float boxR = sqrt(3) * sigmaHi;

        TransformedDomainBoxFilter(img, satX, dIdx, boxR);
        transposeB(img,imgT);

        TransformedDomainBoxFilter(imgT,satY,dIdyT,boxR);
        transposeB(imgT,img);
    }


    // cleanup
    dIcdx.free();
    dIcdy.free();
    dIdx.free();
    dIdy.free();
    dIdyT.free();

    satX.free();
    satY.free();

    imgT.free();

    FP_CALL_END(FunP::ID_ALL);
}



}

#endif // NC_H
