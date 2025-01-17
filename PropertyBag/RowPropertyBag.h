#pragma once
#include <PropertyBag/PropertyBag.h>
#include <UI/Controls/SortList/SortListData.h>

namespace propertybag
{
	class RowPropertyBag : public IMAPIPropertyBag
	{
	public:
		RowPropertyBag(controls::sortlistdata::SortListData* lpListData);
		virtual ~RowPropertyBag();

		ULONG GetFlags() override;
		propBagType GetType() override;
		bool IsEqual(LPMAPIPROPERTYBAG lpPropBag) override;

		_Check_return_ LPMAPIPROP GetMAPIProp() override;

		_Check_return_ HRESULT Commit() override;
		_Check_return_ HRESULT GetAllProps(ULONG FAR* lpcValues, LPSPropValue FAR* lppPropArray) override;
		_Check_return_ HRESULT GetProps(
			LPSPropTagArray lpPropTagArray,
			ULONG ulFlags,
			ULONG FAR* lpcValues,
			LPSPropValue FAR* lppPropArray) override;
		_Check_return_ HRESULT GetProp(ULONG ulPropTag, LPSPropValue FAR* lppProp) override;
		void FreeBuffer(LPSPropValue lpProp) override;
		_Check_return_ HRESULT SetProps(ULONG cValues, LPSPropValue lpPropArray) override;
		_Check_return_ HRESULT SetProp(LPSPropValue lpProp) override;
		_Check_return_ HRESULT DeleteProp(ULONG ulPropTag) override;

	private:
		controls::sortlistdata::SortListData* m_lpListData;

		ULONG m_cValues{};
		LPSPropValue m_lpProps{};
		bool m_bRowModified{};
	};
} // namespace propertybag