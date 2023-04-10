/*
 * Copyright (c) 2020, NVIDIA CORPORATION. All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

#include "jetson-utils/videoSource.h"
#include "jetson-utils/videoOutput.h"
#include "jetson-inference/detectNet.h"
#include <signal.h>

int main()
{
    // Create input stream
    videoSource* input = videoSource::Create("csi://0");

    if (!input)
    {
        printf("Failed to create input stream\n");
        return 1;
    }

    // Create output stream
    videoOutput* output = videoOutput::Create("display://0");

    if (!output)
    {
        printf("Failed to create output stream\n");
        return 1;
    }

    // Create detection network
    detectNet* net = detectNet::Create(detectNet::NetworkType::SSD_MOBILENET_V2);

    if (!net)
    {
        printf("Failed to load detectNet model\n");
        return 1;
    }

    // Parse overlay flags
    const uint32_t overlayFlags = detectNet::OverlayFlagsFromStr("box,labels,conf");

    // Processing loop
    while (true)
    {
        // Capture next image
        uchar3* image = NULL;

        if (!input->Capture(&image, 1000))
        {
            // Check for end of stream
            if (!input->IsStreaming())
                break;

            printf("Failed to capture video frame\n");
            continue;
        }

        // Detect objects in the frame
        detectNet::Detection* detections = NULL;

        const int numDetections = net->Detect(image, input->GetWidth(), input->GetHeight(), &detections, overlayFlags);

        if (numDetections > 0)
        {
            printf("%i objects detected\n", numDetections);

            for (int n = 0; n < numDetections; n++)
            {
                printf("Detected obj %i  class #%u (%s)  confidence=%f\n", n, detections[n].ClassID, net->GetClassDesc(detections[n].ClassID), detections[n].Confidence);
                printf("Bounding box %i  (%f, %f)  (%f, %f)  w=%f  h=%f\n", n, detections[n].Left, detections[n].Top, detections[n].Right, detections[n].Bottom, detections[n].Width(), detections[n].Height());
            }
        }

        // Render outputs
        if (output != NULL)
        {
            output->Render(image, input->GetWidth(), input->GetHeight());

            // Update the status bar
            char str[256];
            sprintf(str, "TensorRT %i.%i.%i | Network %.0f FPS", NV_TENSORRT_MAJOR, NV_TENSORRT_MINOR, NV_TENSORRT_PATCH, net->GetNetworkFPS());
            output->SetStatus(str);

            // Check if the user quit
            if (!output->IsStreaming())
                break;
        }

        // Print out timing info
        net->PrintProfilerTimes();
    }

    // Destroy resources
    SAFE_DELETE(input);
    SAFE_DELETE(output);
    SAFE_DELETE(net);

    return 0;
}
