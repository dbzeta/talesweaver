#include "stdafx.h"
#include "cWICImagingFactory.h"
#include <assert.h>

std::shared_ptr<cWICImagingFactory> cWICImagingFactory::m_pInstance;

cWICImagingFactory::cWICImagingFactory()
	: m_pWICImagingFactory(nullptr)
{
	HRESULT hr = CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER,
		IID_IWICImagingFactory, (LPVOID*)&m_pWICImagingFactory);
	assert(SUCCEEDED(hr));
}

IWICImagingFactory* cWICImagingFactory::GetFactory()  const
{
	assert(m_pWICImagingFactory);
	return m_pWICImagingFactory;
}