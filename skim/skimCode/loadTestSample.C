
TChain *loadTestSample()
{
  TChain *ch = new TChain("datatree");
  ch->Add("/data/chocula/villaa/k100Sim_Data/captureCalroot/GenericShield_PuBeCoin_0x001b_10M_1466092351_000_000_000.root");
  ch->Add("/data/chocula/villaa/k100Sim_Data/captureCalroot/GenericShield_PuBeCoin_0x001b_10M_1466181759_000_000_001.root");
  ch->Add("/data/chocula/villaa/k100Sim_Data/captureCalroot/GenericShield_PuBeCoin_0x001b_10M_1466287414_000_000_002.root");
  ch->Add("/data/chocula/villaa/k100Sim_Data/captureCalroot/GenericShield_PuBeCoin_0x001b_10M_1466381461_000_000_003.root");
  ch->Add("/data/chocula/villaa/k100Sim_Data/captureCalroot/GenericShield_PuBeCoin_0x001b_10M_1466462947_000_000_004.root");
  ch->Add("/data/chocula/villaa/k100Sim_Data/captureCalroot/GenericShield_PuBeCoin_0x001b_10M_1466547728_000_000_005.root");
  ch->Add("/data/chocula/villaa/k100Sim_Data/captureCalroot/GenericShield_PuBeCoin_0x001b_10M_1466623002_000_000_006.root");
  ch->Add("/data/chocula/villaa/k100Sim_Data/captureCalroot/GenericShield_PuBeCoin_0x001b_10M_1466735933_000_000_007.root");
  ch->Add("/data/chocula/villaa/k100Sim_Data/captureCalroot/GenericShield_PuBeCoin_0x001b_10M_1466863933_000_000_008.root");
  ch->Add("/data/chocula/villaa/k100Sim_Data/captureCalroot/GenericShield_PuBeCoin_0x001b_10M_1467019877_000_000_009.root");

  return ch;
}
