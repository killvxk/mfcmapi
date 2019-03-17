#pragma once
#include <core/smartview/SmartViewParser.h>
#include <core/smartview/block/blockStringA.h>
#include <core/smartview/block/blockStringW.h>
#include <core/smartview/block/blockT.h>

namespace smartview
{
	struct VerbData
	{
		blockT<DWORD> VerbType;
		blockT<BYTE> DisplayNameCount;
		std::shared_ptr<blockStringA> DisplayName = emptySA();
		blockT<BYTE> MsgClsNameCount;
		std::shared_ptr<blockStringA> MsgClsName = emptySA();
		blockT<BYTE> Internal1StringCount;
		std::shared_ptr<blockStringA> Internal1String = emptySA();
		blockT<BYTE> DisplayNameCountRepeat;
		std::shared_ptr<blockStringA> DisplayNameRepeat = emptySA();
		blockT<DWORD> Internal2;
		blockT<BYTE> Internal3;
		blockT<DWORD> fUseUSHeaders;
		blockT<DWORD> Internal4;
		blockT<DWORD> SendBehavior;
		blockT<DWORD> Internal5;
		blockT<DWORD> ID;
		blockT<DWORD> Internal6;

		VerbData(std::shared_ptr<binaryParser>& parser);
	};

	struct VerbExtraData
	{
		blockT<BYTE> DisplayNameCount;
		std::shared_ptr<blockStringW> DisplayName = emptySW();
		blockT<BYTE> DisplayNameCountRepeat;
		std::shared_ptr<blockStringW> DisplayNameRepeat = emptySW();

		VerbExtraData(std::shared_ptr<binaryParser>& parser);
	};

	class VerbStream : public SmartViewParser
	{
	private:
		void Parse() override;
		void ParseBlocks() override;

		blockT<WORD> m_Version;
		blockT<DWORD> m_Count;
		std::vector<std::shared_ptr<VerbData>> m_lpVerbData;
		blockT<WORD> m_Version2;
		std::vector<std::shared_ptr<VerbExtraData>> m_lpVerbExtraData;
	};
} // namespace smartview