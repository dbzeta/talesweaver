#pragma once

#include <memory>
#include <wincodec.h>
#include <atlcomcli.h>

class cWICImagingFactory
{
public:
	inline static cWICImagingFactory& GetInstance()
	{
		if (nullptr == m_pInstance.get())
			m_pInstance.reset(new cWICImagingFactory());
		return *m_pInstance;
	}

	virtual IWICImagingFactory* GetFactory() const;

protected:
	CComPtr<IWICImagingFactory> m_pWICImagingFactory;

private:
	cWICImagingFactory();   // Private because singleton
	static std::shared_ptr<cWICImagingFactory> m_pInstance;
};