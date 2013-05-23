#ifndef NC_H
#define NC_H

#include "common.h"
#include <cstring>

#define MAX_DIV_ARRAY_VALUE 255
const float DIV_ARRAY[(MAX_DIV_ARRAY_VALUE)+1] = {1.0/0.0, 1.0/1.0, 1.0/2.0, 1.0/3.0, 1.0/4.0, 1.0/5.0, 1.0/6.0, 1.0/7.0, 1.0/8.0, 1.0/9.0, 1.0/10.0, 1.0/11.0, 1.0/12.0, 1.0/13.0, 1.0/14.0, 1.0/15.0, 1.0/16.0, 1.0/17.0, 1.0/18.0, 1.0/19.0, 1.0/20.0, 1.0/21.0, 1.0/22.0, 1.0/23.0, 1.0/24.0, 1.0/25.0, 1.0/26.0, 1.0/27.0, 1.0/28.0, 1.0/29.0, 1.0/30.0, 1.0/31.0, 1.0/32.0, 1.0/33.0, 1.0/34.0, 1.0/35.0, 1.0/36.0, 1.0/37.0, 1.0/38.0, 1.0/39.0, 1.0/40.0, 1.0/41.0, 1.0/42.0, 1.0/43.0, 1.0/44.0, 1.0/45.0, 1.0/46.0, 1.0/47.0, 1.0/48.0, 1.0/49.0, 1.0/50.0, 1.0/51.0, 1.0/52.0, 1.0/53.0, 1.0/54.0, 1.0/55.0, 1.0/56.0, 1.0/57.0, 1.0/58.0, 1.0/59.0, 1.0/60.0, 1.0/61.0, 1.0/62.0, 1.0/63.0, 1.0/64.0, 1.0/65.0, 1.0/66.0, 1.0/67.0, 1.0/68.0, 1.0/69.0, 1.0/70.0, 1.0/71.0, 1.0/72.0, 1.0/73.0, 1.0/74.0, 1.0/75.0, 1.0/76.0, 1.0/77.0, 1.0/78.0, 1.0/79.0, 1.0/80.0, 1.0/81.0, 1.0/82.0, 1.0/83.0, 1.0/84.0, 1.0/85.0, 1.0/86.0, 1.0/87.0, 1.0/88.0, 1.0/89.0, 1.0/90.0, 1.0/91.0, 1.0/92.0, 1.0/93.0, 1.0/94.0, 1.0/95.0, 1.0/96.0, 1.0/97.0, 1.0/98.0, 1.0/99.0, 1.0/100.0, 1.0/101.0, 1.0/102.0, 1.0/103.0, 1.0/104.0, 1.0/105.0, 1.0/106.0, 1.0/107.0, 1.0/108.0, 1.0/109.0, 1.0/110.0, 1.0/111.0, 1.0/112.0, 1.0/113.0, 1.0/114.0, 1.0/115.0, 1.0/116.0, 1.0/117.0, 1.0/118.0, 1.0/119.0, 1.0/120.0, 1.0/121.0, 1.0/122.0, 1.0/123.0, 1.0/124.0, 1.0/125.0, 1.0/126.0, 1.0/127.0, 1.0/128.0, 1.0/129.0, 1.0/130.0, 1.0/131.0, 1.0/132.0, 1.0/133.0, 1.0/134.0, 1.0/135.0, 1.0/136.0, 1.0/137.0, 1.0/138.0, 1.0/139.0, 1.0/140.0, 1.0/141.0, 1.0/142.0, 1.0/143.0, 1.0/144.0, 1.0/145.0, 1.0/146.0, 1.0/147.0, 1.0/148.0, 1.0/149.0, 1.0/150.0, 1.0/151.0, 1.0/152.0, 1.0/153.0, 1.0/154.0, 1.0/155.0, 1.0/156.0, 1.0/157.0, 1.0/158.0, 1.0/159.0, 1.0/160.0, 1.0/161.0, 1.0/162.0, 1.0/163.0, 1.0/164.0, 1.0/165.0, 1.0/166.0, 1.0/167.0, 1.0/168.0, 1.0/169.0, 1.0/170.0, 1.0/171.0, 1.0/172.0, 1.0/173.0, 1.0/174.0, 1.0/175.0, 1.0/176.0, 1.0/177.0, 1.0/178.0, 1.0/179.0, 1.0/180.0, 1.0/181.0, 1.0/182.0, 1.0/183.0, 1.0/184.0, 1.0/185.0, 1.0/186.0, 1.0/187.0, 1.0/188.0, 1.0/189.0, 1.0/190.0, 1.0/191.0, 1.0/192.0, 1.0/193.0, 1.0/194.0, 1.0/195.0, 1.0/196.0, 1.0/197.0, 1.0/198.0, 1.0/199.0, 1.0/200.0, 1.0/201.0, 1.0/202.0, 1.0/203.0, 1.0/204.0, 1.0/205.0, 1.0/206.0, 1.0/207.0, 1.0/208.0, 1.0/209.0, 1.0/210.0, 1.0/211.0, 1.0/212.0, 1.0/213.0, 1.0/214.0, 1.0/215.0, 1.0/216.0, 1.0/217.0, 1.0/218.0, 1.0/219.0, 1.0/220.0, 1.0/221.0, 1.0/222.0, 1.0/223.0, 1.0/224.0, 1.0/225.0, 1.0/226.0, 1.0/227.0, 1.0/228.0, 1.0/229.0, 1.0/230.0, 1.0/231.0, 1.0/232.0, 1.0/233.0, 1.0/234.0, 1.0/235.0, 1.0/236.0, 1.0/237.0, 1.0/238.0, 1.0/239.0, 1.0/240.0, 1.0/241.0, 1.0/242.0, 1.0/243.0, 1.0/244.0, 1.0/245.0, 1.0/246.0, 1.0/247.0, 1.0/248.0, 1.0/249.0, 1.0/250.0, 1.0/251.0, 1.0/252.0, 1.0/253.0, 1.0/254.0, 1.0/255.0 };
// generated with ",".join(map(lambda l: str(1.0)+"/"+str(float(l)), range(0,101)))

namespace NC
{

void TransformedDomainBoxFilter(Mat2<float3>& img,
                                Mat2<float3>& imgOut,
                                Mat2<float> dIdx, float boxR)
{
    FP_CALL_START(FunP::ID_boxFilter);

    const uint W = img.width;
    const uint H = img.height;

    for (uint i=0; i<H; i++)
    {
        uint posL = 0;
        uint posR = 0;

        // row sat
        float3 sum; sum.r = sum.g = sum.b = 0;

        for (uint j=0; j<W; j++)
        {
            uint idx = i*W + j;
            uint idxT = j*H + i;

            // compute box filter bounds
            float dtL = dIdx.data[idx] - boxR;
            float dtR = dIdx.data[idx] + boxR;

            // update box filter window
            while (dIdx.data[i*W+posL] < dtL && posL < W-1)
            {
                sum.r -= img.data[i*W+posL].r;
                sum.g -= img.data[i*W+posL].g;
                sum.b -= img.data[i*W+posL].b;
                posL++;
            }
            while (posR < W && dIdx.data[i*W+posR] < dtR )  // attention, allows for index = W
            {
                sum.r += img.data[i*W+posR].r;
                sum.g += img.data[i*W+posR].g;
                sum.b += img.data[i*W+posR].b;
                posR++;
            }

            int delta = posR - posL;
            float invD;
            if (delta <= (MAX_DIV_ARRAY_VALUE)) {
                invD = DIV_ARRAY[delta];
            } else
            {
                invD = 1.0f / delta;
            }

            imgOut.data[idxT].r = sum.r * invD;
            imgOut.data[idxT].g = sum.g * invD;
            imgOut.data[idxT].b = sum.b * invD;
        }
    }

    FP_CALL_END(FunP::ID_boxFilter);
}


void filter(Mat2<float3>& img, float sigma_s, float sigma_r, uint nIterations)
{
    FP_CALL_START(FunP::ID_ALL);
    // Estimate horizontal and vertical partial derivatives using finite differences.

    // Compute the l1-norm distance of neighbor pixels.
    FP_CALL_START(FunP::ID_domainTransform);

    const uint W = img.width;
    const uint H = img.height;

    float s = sigma_s/sigma_r;

    Mat2<float> dIdx(W,H);
    Mat2<float> dIdy(W,H);

    for (uint j=0; j<W; j++)
    {
        dIdy.data[j] = 1.0f;
    }

    for (uint i=0; i<H-1; i++)
    {
        dIdx.data[i*W] = 1.0f;
        for (uint j=0; j<W-1; j++)
        {
            uint idx = i*W + j;
            dIdx.data[idx+1] = 1.0f +
                               s*(fabs(img.data[idx+1].r - img.data[idx].r) +
                                  fabs(img.data[idx+1].g - img.data[idx].g) +
                                  fabs(img.data[idx+1].b - img.data[idx].b));
            dIdy.data[idx+W] = 1.0f +
                               s*(fabs(img.data[idx+W].r - img.data[idx].r) +
                                  fabs(img.data[idx+W].g - img.data[idx].g) +
                                  fabs(img.data[idx+W].b - img.data[idx].b));
        }
    }

    dIdx.data[(H-1)*W] = 1.0f;
    for (uint j=0; j<W-1; j++)
    {
        uint idx = (H-1)*W + j;
        dIdx.data[idx+1] = 1.0f +
                           s*(fabs(img.data[idx+1].r - img.data[idx].r) +
                              fabs(img.data[idx+1].g - img.data[idx].g) +
                              fabs(img.data[idx+1].b - img.data[idx].b));
    }

    for (uint i=0; i<H-1; i++)
    {
        uint idx = i*W + (W-1);
        dIdy.data[idx+W] = 1.0f +
                           s*(fabs(img.data[idx+W].r - img.data[idx].r) +
                              fabs(img.data[idx+W].g - img.data[idx].g) +
                              fabs(img.data[idx+W].b - img.data[idx].b));
    }


    FP_CALL_END(FunP::ID_domainTransform);

    Mat2<float> dIdyT(H,W);

    cumsumX(dIdx);
    transposeB(dIdy,dIdyT);
    cumsumX(dIdyT);

    Mat2<float3> imgT(img.height,img.width);

    for(uint i=0; i<nIterations; i++)
    {
        // Compute the sigma value for this iteration
        float sigmaHi = sigma_s * sqrt(3) * powf(2.0,(nIterations - (i+1))) / sqrt(powf(4,nIterations)-1);
        // Compute the radius of the box filter with the desired variance.
        float boxR = sqrt(3) * sigmaHi;

        TransformedDomainBoxFilter(img,imgT, dIdx, boxR);
//        transposeB(img,imgT);

        TransformedDomainBoxFilter(imgT,img,dIdyT,boxR);
//        transposeB(imgT,img);
    }


    // cleanup
    dIdx.free();
    dIdy.free();
    dIdyT.free();

    imgT.free();

    FP_CALL_END(FunP::ID_ALL);
}



}

#endif // NC_H
