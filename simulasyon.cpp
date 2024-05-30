#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/applications-module.h"
#include "ns3/mobility-module.h"
#include "ns3/nr-module.h"
#include "ns3/config-store.h"

using namespace ns3;

NS_LOG_COMPONENT_DEFINE ("5GSimulation");

int main (int argc, char *argv[])
{
    // Log bileşenini etkinleştir
    LogComponentEnable ("NrHelper", LOG_LEVEL_INFO);

    // Komut satırı argümanlarını işleme
    CommandLine cmd;
    cmd.Parse (argc, argv);

    // Node'ları oluştur
    NodeContainer ueNodes;
    ueNodes.Create (1);
    NodeContainer enbNodes;
    enbNodes.Create (1);

    // Hareketlilik modeli tanımlama
    MobilityHelper mobility;
    mobility.SetMobilityModel ("ns3::ConstantPositionMobilityModel");
    mobility.Install (ueNodes);
    mobility.Install (enbNodes);

    // İnternet yığını kurulum
    InternetStackHelper internet;
    internet.Install (ueNodes);
    internet.Install (enbNodes);

    // NR (5G) bileşenlerinin oluşturulması
    Ptr<NrHelper> nrHelper = CreateObject<NrHelper> ();

    // Kanal modeli ve PHY katmanı ayarları
    Ptr<PointToPointEpcHelper> epcHelper = CreateObject<PointToPointEpcHelper> ();
    nrHelper->SetEpcHelper (epcHelper);

    Ptr<Node> pgw = epcHelper->GetPgwNode ();
    InternetStackHelper internet;
    internet.Install (pgw);

    Ipv4AddressHelper address;
    address.SetBase ("1.0.0.0", "255.0.0.0");
    Ipv4InterfaceContainer internetIpIfaces = address.Assign (ueDevices);

    // eNodeB ve UE'lerin oluşturulması
    NetDeviceContainer enbNetDev = nrHelper->InstallEnbDevice (enbNodes);
    NetDeviceContainer ueNetDev = nrHelper->InstallUeDevice (ueNodes);

    // IP adresi atama
    internet.Assign (ueNetDev);

    // Uygulama kurulumları
    uint16_t dlPort = 1234;
    ApplicationContainer serverApps;
    UdpServerHelper myServer (dlPort);
    serverApps.Add (myServer.Install (ueNodes.Get (0)));

    ApplicationContainer clientApps;
    UdpClientHelper myClient (ueIpIfaces.GetAddress (0), dlPort);
    myClient.SetAttribute ("MaxPackets", UintegerValue (1000000));
    myClient.SetAttribute ("Interval", TimeValue (MilliSeconds (10)));
    myClient.SetAttribute ("PacketSize", UintegerValue (1024));
    clientApps.Add (myClient.Install (remoteHost));

    serverApps.Start (Seconds (0.1));
    clientApps.Start (Seconds (0.1));

    Simulator::Stop (Seconds (10.0));
    Simulator::Run ();
    Simulator::Destroy ();

    return 0;
}
