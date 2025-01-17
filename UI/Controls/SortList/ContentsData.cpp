#include <StdAfx.h>
#include <UI/Controls/SortList/ContentsData.h>
#include <core/utility/strings.h>
#include <core/utility/output.h>
#include <core/mapi/mapiFunctions.h>

namespace controls
{
	namespace sortlistdata
	{
		ContentsData::ContentsData(_In_ LPSRow lpsRowData)
		{
			m_lpEntryID = nullptr;
			m_lpLongtermID = nullptr;
			m_lpInstanceKey = nullptr;
			m_lpServiceUID = nullptr;
			m_lpProviderUID = nullptr;
			m_ulAttachNum = 0;
			m_ulAttachMethod = 0;
			m_ulRowID = 0;
			m_ulRowType = 0;

			if (!lpsRowData) return;

			// Save the instance key into lpData
			auto lpProp = PpropFindProp(lpsRowData->lpProps, lpsRowData->cValues, PR_INSTANCE_KEY);
			if (lpProp && PR_INSTANCE_KEY == lpProp->ulPropTag)
			{
				m_lpInstanceKey = mapi::CopySBinary(&lpProp->Value.bin);
			}

			// Save the attachment number into lpData
			lpProp = PpropFindProp(lpsRowData->lpProps, lpsRowData->cValues, PR_ATTACH_NUM);
			if (lpProp && PR_ATTACH_NUM == lpProp->ulPropTag)
			{
				output::DebugPrint(output::DBGGeneric, L"\tPR_ATTACH_NUM = %d\n", lpProp->Value.l);
				m_ulAttachNum = lpProp->Value.l;
			}

			lpProp = PpropFindProp(lpsRowData->lpProps, lpsRowData->cValues, PR_ATTACH_METHOD);
			if (lpProp && PR_ATTACH_METHOD == lpProp->ulPropTag)
			{
				output::DebugPrint(output::DBGGeneric, L"\tPR_ATTACH_METHOD = %d\n", lpProp->Value.l);
				m_ulAttachMethod = lpProp->Value.l;
			}

			// Save the row ID (recipients) into lpData
			lpProp = PpropFindProp(lpsRowData->lpProps, lpsRowData->cValues, PR_ROWID);
			if (lpProp && PR_ROWID == lpProp->ulPropTag)
			{
				output::DebugPrint(output::DBGGeneric, L"\tPR_ROWID = %d\n", lpProp->Value.l);
				m_ulRowID = lpProp->Value.l;
			}

			// Save the row type (header/leaf) into lpData
			lpProp = PpropFindProp(lpsRowData->lpProps, lpsRowData->cValues, PR_ROW_TYPE);
			if (lpProp && PR_ROW_TYPE == lpProp->ulPropTag)
			{
				output::DebugPrint(output::DBGGeneric, L"\tPR_ROW_TYPE = %d\n", lpProp->Value.l);
				m_ulRowType = lpProp->Value.l;
			}

			// Save the Entry ID into lpData
			lpProp = PpropFindProp(lpsRowData->lpProps, lpsRowData->cValues, PR_ENTRYID);
			if (lpProp && PR_ENTRYID == lpProp->ulPropTag)
			{
				m_lpEntryID = mapi::CopySBinary(&lpProp->Value.bin);
			}

			// Save the Longterm Entry ID into lpData
			lpProp = PpropFindProp(lpsRowData->lpProps, lpsRowData->cValues, PR_LONGTERM_ENTRYID_FROM_TABLE);
			if (lpProp && PR_LONGTERM_ENTRYID_FROM_TABLE == lpProp->ulPropTag)
			{
				m_lpLongtermID = mapi::CopySBinary(&lpProp->Value.bin);
			}

			// Save the Service ID into lpData
			lpProp = PpropFindProp(lpsRowData->lpProps, lpsRowData->cValues, PR_SERVICE_UID);
			if (lpProp && PR_SERVICE_UID == lpProp->ulPropTag)
			{
				m_lpServiceUID = mapi::CopySBinary(&lpProp->Value.bin);
			}

			// Save the Provider ID into lpData
			lpProp = PpropFindProp(lpsRowData->lpProps, lpsRowData->cValues, PR_PROVIDER_UID);
			if (lpProp && PR_PROVIDER_UID == lpProp->ulPropTag)
			{
				m_lpProviderUID = mapi::CopySBinary(&lpProp->Value.bin);
			}

			// Save the DisplayName into lpData
			lpProp = PpropFindProp(
				lpsRowData->lpProps,
				lpsRowData->cValues,
				PR_DISPLAY_NAME_A); // We pull this property for profiles, which do not support Unicode
			if (strings::CheckStringProp(lpProp, PT_STRING8))
			{
				m_szProfileDisplayName = lpProp->Value.lpszA;
				output::DebugPrint(output::DBGGeneric, L"\tPR_DISPLAY_NAME_A = %hs\n", m_szProfileDisplayName.c_str());
			}

			// Save the e-mail address (if it exists on the object) into lpData
			lpProp = PpropFindProp(lpsRowData->lpProps, lpsRowData->cValues, PR_EMAIL_ADDRESS);
			if (strings::CheckStringProp(lpProp, PT_TSTRING))
			{
				m_szDN = strings::LPCTSTRToWstring(lpProp->Value.LPSZ);
				output::DebugPrint(output::DBGGeneric, L"\tPR_EMAIL_ADDRESS = %ws\n", m_szDN.c_str());
			}
		}

		ContentsData::~ContentsData()
		{
			MAPIFreeBuffer(m_lpInstanceKey);
			MAPIFreeBuffer(m_lpEntryID);
			MAPIFreeBuffer(m_lpLongtermID);
			MAPIFreeBuffer(m_lpServiceUID);
			MAPIFreeBuffer(m_lpProviderUID);
		}
	} // namespace sortlistdata
} // namespace controls