#pragma once
#include <Windows.h>
#include <Mmdeviceapi.h>
#include <Audioclient.h>
#include <iostream>

#pragma comment(lib, "Mmdevapi.lib")
#pragma comment(lib, "Winmm.lib")
using namespace std;
class CaptureStream
{
public:
    CaptureStream();
    ~CaptureStream();

    bool Initialize();
    bool StartCapture();
    void StopCapture();
    IAudioCaptureClient* getpCaptureClient() {
        return pCaptureClient;
    }
    WAVEFORMATEX* getpwfx() {
        return pwfx;
    }
    IAudioClient* getpAudioClient() {
        return pAudioClient;
    }

    // Method to get the address of the audio buffer
    BYTE* GetBufferAddress();
private:
    IMMDeviceEnumerator* pEnumerator = NULL;
    IMMDevice* pDevice = NULL;
    IAudioClient* pAudioClient = NULL;
    IAudioCaptureClient* pCaptureClient = NULL;
    WAVEFORMATEX* pwfx = NULL;
};

CaptureStream::CaptureStream() : pEnumerator(nullptr), pDevice(nullptr), pAudioClient(nullptr), pCaptureClient(nullptr), pwfx(nullptr)
{
    HRESULT hr = CoInitialize(NULL);
    if (FAILED(hr))
    {
        std::cerr << "failed to initialize" << std::endl;
        pCaptureClient->Release();
        pAudioClient->Release();
        CoUninitialize();
    }
}

CaptureStream::~CaptureStream()
{
    if (pCaptureClient)
    {
        pCaptureClient->Release();
        pCaptureClient = nullptr;
    }

    if (pAudioClient)
    {
        pAudioClient->Stop();
        pAudioClient->Release();
        pAudioClient = nullptr;
    }

    if (pwfx)
    {
        CoTaskMemFree(pwfx);
        pwfx = nullptr;
    }

    if (pDevice)
    {
        pDevice->Release();
        pDevice = nullptr;
    }

    if (pEnumerator)
    {
        pEnumerator->Release();
        pEnumerator = nullptr;
    }

    CoUninitialize();
}

bool CaptureStream::Initialize()
{
    HRESULT hr = CoCreateInstance(
        __uuidof(MMDeviceEnumerator),
        NULL,
        CLSCTX_ALL,
        __uuidof(IMMDeviceEnumerator),
        (void**)&pEnumerator
    );

    if (FAILED(hr))
    {
        std::cerr << "Failed to initialize COM or get device enumerator." << std::endl;
        return 1;
    }

    hr = pEnumerator->GetDefaultAudioEndpoint(eRender, eConsole, &pDevice);
    pEnumerator->Release();

    if (FAILED(hr))
    {
        std::cerr << "Failed to get the default audio endpoint." << std::endl;
        return 1;
    }

    // Get the audio client and audio capture client interfaces for loopback capture
    hr = pDevice->Activate(__uuidof(IAudioClient), CLSCTX_ALL, NULL, (void**)&pAudioClient);
    pDevice->Release();

    if (FAILED(hr))
    {
        std::cerr << "Failed to activate the audio client." << std::endl;
        return 1;
    }

    hr = pAudioClient->GetMixFormat(&pwfx);

    if (FAILED(hr))
    {
        std::cerr << "Failed to get the mix format." << std::endl;
        return 1;
    }

    // Initialize the audio client for loopback capture
    REFERENCE_TIME bufferDuration = 853333;
    hr = pAudioClient->Initialize(AUDCLNT_SHAREMODE_SHARED, AUDCLNT_STREAMFLAGS_LOOPBACK, bufferDuration, 0, pwfx, NULL);
    CoTaskMemFree(pwfx);

    if (FAILED(hr))
    {
        std::cerr << "Failed to initialize the audio client." << std::endl;
        return 1;
    }

    hr = pAudioClient->GetService(__uuidof(IAudioCaptureClient), (void**)&pCaptureClient);

    if (FAILED(hr))
    {
        std::cerr << "Failed to get the audio capture client." << std::endl;
        pAudioClient->Release(); // Release the audio client before exiting
        CoUninitialize();
        return 1;
    }

    // Start audio loopback capture
    hr = pAudioClient->Start();

    if (FAILED(hr))
    {
        std::cerr << "Failed to start audio loopback capture." << std::endl;
        pCaptureClient->Release();
        pAudioClient->Release();
        CoUninitialize();
        return 1;
    }

    return true;
}

bool CaptureStream::StartCapture()
{
    HRESULT hr = pAudioClient->Start();

    if (FAILED(hr))
    {
        std::cerr << "Failed to start audio loopback capture." << std::endl;
        pCaptureClient->Release();
        pAudioClient->Release();
        CoUninitialize();
        return 1;
    }

    return SUCCEEDED(hr);
}

void CaptureStream::StopCapture()
{
    pAudioClient->Stop();
}



BYTE* CaptureStream::GetBufferAddress()
{
    BYTE* pData;
    DWORD flags;
    UINT32 packetSize;
    HRESULT hr;
    hr = pCaptureClient->GetBuffer(&pData, &packetSize, &flags, NULL, NULL);
    if (FAILED(hr))
    {
        std::cerr << "Failed to get capture buffer." << std::endl;
    }
    if (pData == NULL)
    {
        // Fill the buffer with 0's
    }
    return pData;
}
