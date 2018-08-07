// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The Btcgreen developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainparams.h"

#include "random.h"
#include "util.h"
#include "utilstrencodings.h"

#include <assert.h>

#include <boost/assign/list_of.hpp>

using namespace std;
using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

/**	
* Main network	
*/

//! Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress>& vSeedsOut, const SeedSpec6* data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7 * 24 * 60 * 60;
    for (unsigned int i = 0; i < count; i++) {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

/**	
* What makes a good checkpoint block?	
* + Is surrounded by blocks with reasonable timestamps	
* (no blocks before with a timestamp after, none after with	
* timestamp before)	
* + Contains no strange transactions	
*/

static Checkpoints::MapCheckpoints mapCheckpoints =
    boost::assign::map_list_of(0, uint256("0x000004a81376239090da0d1dd2deb07c3c8a06760d4ead03f315df7b79ecaf49"));
;
static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1533544607, // * UNIX timestamp of last checkpoint block
    0,          // * total number of transactions between genesis and last checkpoint
    // (the tx=... number in the SetBestChain debug.log lines)
    2800 // * estimated number of transactions per day after checkpoint
};

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
    boost::assign::map_list_of(0, uint256("00000456321cdcae42965c7de4f28e8df1e93752c7207ad4fd4b0ea5478316dd"));
static const Checkpoints::CCheckpointData dataTestnet = {
    &mapCheckpointsTestnet,
    1533544638,
    0,
    500};

static Checkpoints::MapCheckpoints mapCheckpointsRegtest =
    boost::assign::map_list_of(0, uint256("00000456321cdcae42965c7de4f28e8df1e93752c7207ad4fd4b0ea5478316dd"));
static const Checkpoints::CCheckpointData dataRegtest = {
    &mapCheckpointsRegtest,
    0,
    0,
    0};

class CMainParams : public CChainParams
{
public:
    CMainParams()
    {
        networkID = CBaseChainParams::MAIN;
        strNetworkID = "main";
        /** 	
* The message start string is designed to be unlikely to occur in normal data.	
* The characters are rarely used upper ASCII, not valid as UTF-8, and produce	
* a large 4-byte int at any alignment.	
*/
        pchMessageStart[0] = 0xbf;
        pchMessageStart[1] = 0x0c;
        pchMessageStart[2] = 0x6b;
        pchMessageStart[3] = 0xbd;
        vAlertPubKey = ParseHex("043920540276872d5ac0f2ea041bb7afc6b14a9fe24b67fc6c4a8a8c747205d7b61f04d17a86a21efbbec036abf04fd3e9b27f45a7caf4d2b57b7013f3363fadf7");
        nDefaultPort = 1993 bnProofOfWorkLimit = ~uint256(0) >> 20; // Btcgreen starting difficulty is 1 / 2^12
        nSubsidyHalvingInterval = 210000;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 0;
        nTargetTimespan = 10 * 60 * 60; // Btcgreen: 1 day
        nTargetSpacing = 1 * 60;        // Btcgreen: 2.5 minutes

        /**	
* Build the genesis block. Note that the output of the genesis coinbase cannot	
* be spent as it did not originally exist in the database.	
* 	
* CBlock(hash=00000ffd590b14, ver=1, hashPrevBlock=00000000000000, hashMerkleRoot=e0028e, nTime=1390095618, nBits=1e0ffff0, nNonce=28917698, vtx=1)	
* CTransaction(hash=e0028e, ver=1, vin.size=1, vout.size=1, nLockTime=0)	
* CTxIn(COutPoint(000000, -1), coinbase 04ffff001d01044c5957697265642030392f4a616e2f3230313420546865204772616e64204578706572696d656e7420476f6573204c6976653a204f76657273746f636b2e636f6d204973204e6f7720416363657074696e6720426974636f696e73)	
* CTxOut(nValue=50.00000000, scriptPubKey=0xA9037BAC7050C479B121CF)	
* vMerkleTree: e0028e	
*/
        const char* pszTimestamp = "btcgreen created on 06/08/2018 for APAC Trading House.";
        CMutableTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].nValue = 50 * COIN;
        txNew.vout[0].scriptPubKey = CScript() << ParseHex("04d6fe8d0c61409447ed274c5f1705567221fc585dba79616e1e6eb79fd69d44f4def4d9970e5a8e55ce85eda1a45432741ffc94f07add4e78ae0f3089cc0df31a") << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime = 1533544607;
        genesis.nBits = 0x1e0ffff0;
        genesis.nNonce = 13904;

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x000004a81376239090da0d1dd2deb07c3c8a06760d4ead03f315df7b79ecaf49"));
        assert(genesis.hashMerkleRoot == uint256("0x10289994e660eceb3ef06289004e7fbc86c0057bd8055d335a128645c9eb655b"));

        vSeeds.clear();

        base58Prefixes[PUBKEY_ADDRESS] = list_of(76);                     // Btcgreen addresses start with 'X'
        base58Prefixes[SCRIPT_ADDRESS] = list_of(16);                     // Btcgreen script addresses start with '7'
        base58Prefixes[SECRET_KEY] = list_of(204);                        // Btcgreen private keys start with '7' or 'X'
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x02)(0xFE)(0x52)(0xF8); // Btcgreen BIP32 pubkeys start with 'drkv'
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x02)(0xFE)(0x52)(0xCC); // Btcgreen BIP32 prvkeys start with 'drkp'
        base58Prefixes[EXT_COIN_TYPE] = list_of(0x80000005);              // Btcgreen BIP44 coin type is '5'

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        fRequireRPCPassword = true;
        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = false;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fSkipProofOfWorkCheck = false;
        fTestnetToBeDeprecatedFieldRPC = false;

        nPoolMaxTransactions = 3;
        strSporkKey = "047091249ceed26e3f33da7173b93041ad070b0ff7217289839a5308d193ca3953f1e24590ce80887eecba94ea91991083ecd9fc654152a6deeece2734235c0017";
        strMasternodePaymentsPubKey = "047091249ceed26e3f33da7173b93041ad070b0ff7217289839a5308d193ca3953f1e24590ce80887eecba94ea91991083ecd9fc654152a6deeece2734235c0017";
        strDarksendPoolDummyAddress = "Xq19GqFvajRrEdDHYRKGYjTsQfpV5jyipF";
        nStartMasternodePayments = 1533544607; //Wed, 25 Jun 2014 20:36:16 GMT
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return data;
    }
};
static CMainParams mainParams;

/**	
* Testnet (v3)	
*/
class CTestNetParams : public CMainParams
{
public:
    CTestNetParams()
    {
        networkID = CBaseChainParams::TESTNET;
        strNetworkID = "test";
        pchMessageStart[0] = 0xce;
        pchMessageStart[1] = 0xe2;
        pchMessageStart[2] = 0xca;
        pchMessageStart[3] = 0xff;
        vAlertPubKey = ParseHex("04e68914f52587f1a8f40a4770586a42735d23338e4bba28d9ad1fd998ac04c64ef35a359d210204288baec1ab67d8ee847ac307cf21aa3203bb3fb712909f9909");
        nDefaultPort = 11993;
        nEnforceBlockUpgradeMajority = 51;
        nRejectBlockOutdatedMajority = 75;
        nToCheckBlockUpgradeMajority = 100;
        nMinerThreads = 0;
        nTargetTimespan = 10 * 60 * 60; // Btcgreen: 1 day
        nTargetSpacing = 1 * 60;        // Btcgreen: 2.5 minutes

        //! Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nTime = 1533544638;
        genesis.nNonce = 2916721;

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x00000456321cdcae42965c7de4f28e8df1e93752c7207ad4fd4b0ea5478316dd"));

        vFixedSeeds.clear();
        vSeeds.clear();
        /*vSeeds.push_back(CDNSSeedData("btcgreen.co", "testnet-seed.btcgreen.co"));	
vSeeds.push_back(CDNSSeedData("btcgreen.qa", "testnet-seed.btcgreen.qa"));	
*/
        //legacy seeders

        base58Prefixes[PUBKEY_ADDRESS] = list_of(139);                    // Testnet btcgreen addresses start with 'x' or 'y'
        base58Prefixes[SCRIPT_ADDRESS] = list_of(19);                     // Testnet btcgreen script addresses start with '8' or '9'
        base58Prefixes[SECRET_KEY] = list_of(239);                        // Testnet private keys start with '9' or 'c' (Bitcoin defaults)
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x3a)(0x80)(0x61)(0xa0); // Testnet btcgreen BIP32 pubkeys start with 'DRKV'
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x3a)(0x80)(0x58)(0x37); // Testnet btcgreen BIP32 prvkeys start with 'DRKP'
        base58Prefixes[EXT_COIN_TYPE] = list_of(0x80000001);              // Testnet btcgreen BIP44 coin type is '5' (All coin's testnet default)

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        fRequireRPCPassword = true;
        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = true;

        nPoolMaxTransactions = 2;
        strSporkKey = "044b7d51274b9bf61d29281d7b0ebf0e6d27811e92e508514ec2fde6f2dc7b3094bee3f546b58ec621f12129f0102743f32190edad59e95de5cc1d553c1b5fae9f";
        strMasternodePaymentsPubKey = "044b7d51274b9bf61d29281d7b0ebf0e6d27811e92e508514ec2fde6f2dc7b3094bee3f546b58ec621f12129f0102743f32190edad59e95de5cc1d553c1b5fae9f";
        strDarksendPoolDummyAddress = "y1EZuxhhNMAUofTBEeLqGE1bJrpC2TWRNp";
        nStartMasternodePayments = 1533544638; //Fri, 09 Jan 2015 21:05:58 GMT
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataTestnet;
    }
};
static CTestNetParams testNetParams;

/**	
* Regression test	
*/
class CRegTestParams : public CTestNetParams
{
public:
    CRegTestParams()
    {
        networkID = CBaseChainParams::REGTEST;
        strNetworkID = "regtest";
        pchMessageStart[0] = 0xfc;
        pchMessageStart[1] = 0xc1;
        pchMessageStart[2] = 0xb7;
        pchMessageStart[3] = 0xdc;
        nSubsidyHalvingInterval = 150;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 1;
        nTargetTimespan = 10 * 60 * 60; // Btcgreen: 1 day
        nTargetSpacing = 1 * 60;        // Btcgreen: 2.5 minutes
        bnProofOfWorkLimit = ~uint256(0) >> 1;
        genesis.nTime = 1533544638;
        genesis.nBits = 0x207fffff;
        genesis.nNonce = 2916721;
        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 19931;
        assert(hashGenesisBlock == uint256("0x00000456321cdcae42965c7de4f28e8df1e93752c7207ad4fd4b0ea5478316dd"));

        vFixedSeeds.clear(); //! Regtest mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Regtest mode doesn't have any DNS seeds.

        fRequireRPCPassword = false;
        fMiningRequiresPeers = false;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;
        fTestnetToBeDeprecatedFieldRPC = false;
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataRegtest;
    }
};
static CRegTestParams regTestParams;

/**	
* Unit test	
*/
class CUnitTestParams : public CMainParams, public CModifiableParams
{
public:
    CUnitTestParams()
    {
        networkID = CBaseChainParams::UNITTEST;
        strNetworkID = "unittest";
        nDefaultPort = 18445;
        vFixedSeeds.clear(); //! Unit test mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Unit test mode doesn't have any DNS seeds.

        fRequireRPCPassword = false;
        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = true;
        fAllowMinDifficultyBlocks = false;
        fMineBlocksOnDemand = true;
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        // UnitTest share the same checkpoints as MAIN
        return data;
    }

    //! Published setters to allow changing values in unit test cases
    virtual void setSubsidyHalvingInterval(int anSubsidyHalvingInterval) { nSubsidyHalvingInterval = anSubsidyHalvingInterval; }
    virtual void setEnforceBlockUpgradeMajority(int anEnforceBlockUpgradeMajority) { nEnforceBlockUpgradeMajority = anEnforceBlockUpgradeMajority; }
    virtual void setRejectBlockOutdatedMajority(int anRejectBlockOutdatedMajority) { nRejectBlockOutdatedMajority = anRejectBlockOutdatedMajority; }
    virtual void setToCheckBlockUpgradeMajority(int anToCheckBlockUpgradeMajority) { nToCheckBlockUpgradeMajority = anToCheckBlockUpgradeMajority; }
    virtual void setDefaultConsistencyChecks(bool afDefaultConsistencyChecks) { fDefaultConsistencyChecks = afDefaultConsistencyChecks; }
    virtual void setAllowMinDifficultyBlocks(bool afAllowMinDifficultyBlocks) { fAllowMinDifficultyBlocks = afAllowMinDifficultyBlocks; }
    virtual void setSkipProofOfWorkCheck(bool afSkipProofOfWorkCheck) { fSkipProofOfWorkCheck = afSkipProofOfWorkCheck; }
};
static CUnitTestParams unitTestParams;


static CChainParams* pCurrentParams = 0;

CModifiableParams* ModifiableParams()
{
    assert(pCurrentParams);
    assert(pCurrentParams == &unitTestParams);
    return (CModifiableParams*)&unitTestParams;
}

const CChainParams& Params()
{
    assert(pCurrentParams);
    return *pCurrentParams;
}

CChainParams& Params(CBaseChainParams::Network network)
{
    switch (network) {
    case CBaseChainParams::MAIN:
        return mainParams;
    case CBaseChainParams::TESTNET:
        return testNetParams;
    case CBaseChainParams::REGTEST:
        return regTestParams;
    case CBaseChainParams::UNITTEST:
        return unitTestParams;
    default:
        assert(false && "Unimplemented network");
        return mainParams;
    }
}

void SelectParams(CBaseChainParams::Network network)
{
    SelectBaseParams(network);
    pCurrentParams = &Params(network);
}

bool SelectParamsFromCommandLine()
{
    CBaseChainParams::Network network = NetworkIdFromCommandLine();
    if (network == CBaseChainParams::MAX_NETWORK_TYPES)
        return false;

    SelectParams(network);
    return true;
}
