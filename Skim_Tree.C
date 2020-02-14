void Skim_Trees()
{
  cout<<2<<endl;
  char sample[100];
  ifstream        sample_list;
  sample_list.open("samples.txt");
  cout<<1<<endl;
  TFile   *input_BR[80][500];
  TTree   *input_background[80][500];

  int sample_index = 0;

  FILE    *log;

  log     = fopen("Error.log","w");
  cout<<3<<endl;
  while(1)
    {


      char skimmedfilename[200];

                sample_list >>sample;
                cout<<4<<endl;
                if(!sample_list.good())
                  {
                    cout<<5<<endl;
                    break;
                  }
                {
                  printf("Adding trees from %s sample\n",sample);
                  fprintf(log,"Adding trees from %s sample\n",sample);
                  int           regression;
                  int           sampleIndex;
                  float         weight;
                  float         lep1_pt, lep1_eta, lep1_mass, lep1_phi;
                  float         lep2_pt, lep2_eta, lep2_mass, lep2_phi;
                  float         bjet1_pt, bjet1_eta, bjet1_mass, bjet1_phi, bjet1_DeepCSV;
                  float         bjet1_PtReg, bjet1_PtRegUp, bjet1_PtRegDown, bjet1_bRegRes, bjet1_bReg;
                  float         bjet2_pt, bjet2_eta, bjet2_mass, bjet2_phi, bjet2_DeepCSV;
                  float         bjet2_PtReg, bjet2_PtRegUp, bjet2_PtRegDown, bjet2_bRegRes, bjet2_bReg;
                  float         MET_phi;
                  float         MET_Pt;
                  float         H_mass;
                  float         H_mass_noreg;
                  float         ele1_pt, ele2_pt, muon1_pt, muon2_pt, jet1_pt, jet2_pt;
                  float         Sum_Pt = 0, Jet_pt;
                  int           lepInd1;
                  int           lepInd2;
                  int           hJetInd1;
                  int           hJetInd2;
                  int           isZee, isZmm;
                  int           PV_npvs, Vtype;
                  float         fixedGridRhoFastjetAll;
                  int           i = 1, evtno, iJet, nJet;


                  sprintf(skimmedfilename,"/STORE/VHbb/regression/skim_bkg/skimmed_%s.root",sample);

                  TFile   *skimmed        = new TFile(skimmedfilename,"RECREATE");
                  TTree   *data           = new TTree("Events",   "Regression");

                  data->Branch("weight", &weight, "weight/F");
                  data->Branch("lep1_pt", &lep1_pt, "lep1_pt/F");
                  data->Branch("lep1_eta", &lep1_eta, "lep1_eta/F");
                  data->Branch("lep1_mass", &lep1_mass, "lep1_mass/F");
                  data->Branch("lep1_phi", &lep1_phi, "lep1_phi/F");
                  data->Branch("lep2_pt", &lep2_pt, "lep2_pt/F");
                  data->Branch("lep2_eta", &lep2_eta, "lep2_eta/F");
                  data->Branch("lep2_mass", &lep2_mass, "lep2_mass/F");
                  data->Branch("lep2_phi", &lep2_phi, "lep2_phi/F");
                  data->Branch("bjet1_pt", &bjet1_pt, "bjet1_pt/F");
                  data->Branch("bjet1_eta", &bjet1_eta, "bjet1_eta/F");
                  data->Branch("bjet1_mass", &bjet1_mass, "bjet1_mass/F");
                  data->Branch("bjet1_phi", &bjet1_phi, "bjet1_phi/F");
                  data->Branch("bjet1_DeepCSV", &bjet1_DeepCSV, "bjet1_DeepCSV/F");
                  data->Branch("bjet1_PtReg", &bjet1_PtReg, "bjet1_PtReg/F");
                  data->Branch("bjet1_PtRegUp", &bjet1_PtRegUp, "bjet1_PtRegUp/F");
                  data->Branch("bjet1_PtRegDown", &bjet1_PtRegDown, "bjet1_PtRegDown/F");
                  data->Branch("bjet1_bRegRes", &bjet1_bRegRes, "bjet1_bRegRes/F");
                  data->Branch("bjet2_pt", &bjet2_pt, "bjet2_pt/F");
                  data->Branch("bjet2_eta", &bjet2_eta, "bjet2_eta/F");
                  data->Branch("bjet2_mass", &bjet2_mass, "bjet2_mass/F");
                  data->Branch("bjet2_phi", &bjet2_phi, "bjet2_phi/F");
                  data->Branch("bjet2_DeepCSV", &bjet2_DeepCSV, "bjet2_DeepCSV/F");
                  data->Branch("bjet2_PtReg", &bjet2_PtReg, "bjet2_PtReg/F");
                  data->Branch("bjet2_PtRegUp", &bjet2_PtRegUp, "bjet2_PtRegUp/F");
                  data->Branch("bjet2_PtRegDown", &bjet2_PtRegDown, "bjet2_PtRegDown/F");
                  data->Branch("bjet2_bRegRes", &bjet2_bRegRes, "bjet2_bRegRes/F");
                  data->Branch("MET_phi", &MET_phi, "MET_phi/F");
                  data->Branch("MET_Pt", &MET_Pt, "MET_Pt/F");
                  data->Branch("Sum_Pt", &Sum_Pt, "Sum_Pt/F");
                  data->Branch("H_mass", &H_mass, "H_mass/F");
                  data->Branch("H_mass_noreg", &H_mass_noreg, "H_mass_noreg/F");
                  data->Branch("PV_npvs", &PV_npvs, "PV_npvs/I");
                  data->Branch("Vtype", &Vtype, "Vtype/I");
                  data->Branch("fixedGridRhoFastjetAll", &fixedGridRhoFastjetAll, "fixedGridRhoFastjetAll/F");

                  while(1)
                    {
                      char filename[200],nextfilename[200],secnextfilename[200];

                      sprintf(filename,"/STORE/VHbb/regression/new/%s/output_%s_%d.root",sample,sample,i);
                      ifstream    file,nextfile,secnextfile;
                      file.open(filename);
                      sprintf(nextfilename,"/STORE/VHbb/regression/new/%s/output_%s_%d.root",sample,sample,i+1);
                      nextfile.open(nextfilename);
                      sprintf(secnextfilename,"/STORE/VHbb/regression/new/%s/output_%s_%d.root",sample,sample,i+2);
                      secnextfile.open(secnextfilename);
                      if(!file.is_open() && !nextfile.is_open() && !secnextfile.is_open())
                        {
                          break;
                        }
                      if(!file.is_open())
                        {
                          printf("File %s not found\n",filename);
                          i++;
                          continue;
                        }
                      cout<<filename<<endl;
                      input_BR[sample_index][i]               = new TFile(filename);
                      input_background[sample_index][i]       = (TTree*)input_BR[sample_index][i]->Get("Events");

                      int entries = input_background[sample_index][i]->GetEntries();

                      for(evtno = 0;evtno < entries;evtno++)
                        {
                          input_background[sample_index][i]->GetEntry(evtno);

                          sampleIndex     = input_background[sample_index][i]->GetLeaf("sampleIndex")->GetValue();
                          isZee           = input_background[sample_index][i]->GetLeaf("isZee")->GetValue();
                          isZmm           = input_background[sample_index][i]->GetLeaf("isZmm")->GetValue();
                          regression      = input_background[sample_index][i]->GetLeaf("regression")->GetValue();
                          hJetInd1        = input_background[sample_index][i]->GetLeaf("hJetInd1")->GetValue();
                          hJetInd2        = input_background[sample_index][i]->GetLeaf("hJetInd2")->GetValue();
                          lepInd1         = input_background[sample_index][i]->GetLeaf("lepInd1")->GetValue();
                          lepInd2         = input_background[sample_index][i]->GetLeaf("lepInd2")->GetValue();
                          ele1_pt         = input_background[sample_index][i]->GetLeaf("Electron_pt")->GetValue(lepInd1);
                          ele2_pt         = input_background[sample_index][i]->GetLeaf("Electron_pt")->GetValue(lepInd2);
                          muon1_pt        = input_background[sample_index][i]->GetLeaf("Muon_pt")->GetValue(lepInd1);
                          muon2_pt        = input_background[sample_index][i]->GetLeaf("Muon_pt")->GetValue(lepInd2);
                          jet1_pt         = input_background[sample_index][i]->GetLeaf("Jet_Pt")->GetValue(hJetInd1);
                          jet2_pt         = input_background[sample_index][i]->GetLeaf("Jet_Pt")->GetValue(hJetInd2);
                          nJet            = input_background[sample_index][i]->GetLeaf("nJet")->GetValue();

                          if (regression==10 && ((ele1_pt>25 && ele2_pt>25) || (muon1_pt>25 && muon2_pt>25)) && jet1_pt>25 && jet2_pt>25)
                            {
                              weight          = input_background[sample_index][i]->GetLeaf("weight")->GetValue();
                              MET_Pt          = input_background[sample_index][i]->GetLeaf("MET_Pt")->GetValue();
                              MET_phi         = input_background[sample_index][i]->GetLeaf("MET_phi")->GetValue();
                              H_mass          = input_background[sample_index][i]->GetLeaf("H_mass")->GetValue();
                              H_mass_noreg    = input_background[sample_index][i]->GetLeaf("H_mass_noreg")->GetValue();
                              PV_npvs         = input_background[sample_index][i]->GetLeaf("PV_npvs")->GetValue();
                              fixedGridRhoFastjetAll = input_background[sample_index][i]->GetLeaf("fixedGridRhoFastjetAll")->GetValue();
                              Vtype           = input_background[sample_index][i]->GetLeaf("Vtype")->GetValue();
                              bjet1_pt        = input_background[sample_index][i]->GetLeaf("Jet_Pt")->GetValue(hJetInd1);
                              bjet1_eta       = input_background[sample_index][i]->GetLeaf("Jet_eta")->GetValue(hJetInd1);
                              bjet1_mass      = input_background[sample_index][i]->GetLeaf("Jet_mass")->GetValue(hJetInd1);
                              bjet1_phi       = input_background[sample_index][i]->GetLeaf("Jet_phi")->GetValue(hJetInd1);
                              bjet1_DeepCSV   = input_background[sample_index][i]->GetLeaf("Jet_btagDeepB")->GetValue(hJetInd1);
                              bjet1_PtReg     = input_background[sample_index][i]->GetLeaf("Jet_PtReg")->GetValue(hJetInd1);
                              bjet1_PtRegUp   = input_background[sample_index][i]->GetLeaf("Jet_PtRegUp")->GetValue(hJetInd1);
                              bjet1_PtRegDown = input_background[sample_index][i]->GetLeaf("Jet_PtRegDown")->GetValue(hJetInd1);
                              bjet1_bRegRes   = input_background[sample_index][i]->GetLeaf("Jet_bRegRes")->GetValue(hJetInd1);
                              bjet2_pt        = input_background[sample_index][i]->GetLeaf("Jet_Pt")->GetValue(hJetInd2);
                              bjet2_eta       = input_background[sample_index][i]->GetLeaf("Jet_eta")->GetValue(hJetInd2);
                              bjet2_mass      = input_background[sample_index][i]->GetLeaf("Jet_mass")->GetValue(hJetInd2);
                              bjet2_phi       = input_background[sample_index][i]->GetLeaf("Jet_phi")->GetValue(hJetInd2);
                              bjet2_DeepCSV   = input_background[sample_index][i]->GetLeaf("Jet_btagDeepB")->GetValue(hJetInd2);
                              bjet2_PtReg     = input_background[sample_index][i]->GetLeaf("Jet_PtReg")->GetValue(hJetInd2);
                              bjet2_PtRegUp   = input_background[sample_index][i]->GetLeaf("Jet_PtRegUp")->GetValue(hJetInd2);
                              bjet2_PtRegDown = input_background[sample_index][i]->GetLeaf("Jet_PtRegDown")->GetValue(hJetInd2);
                              bjet2_bRegRes   = input_background[sample_index][i]->GetLeaf("Jet_bRegRes")->GetValue(hJetInd2);


                              if (isZee==1){
                                lep1_pt         = input_background[sample_index][i]->GetLeaf("Electron_pt")->GetValue(lepInd1);
                                lep1_eta        = input_background[sample_index][i]->GetLeaf("Electron_eta")->GetValue(lepInd1);
                                lep1_mass       = input_background[sample_index][i]->GetLeaf("Electron_mass")->GetValue(lepInd1);
                                lep1_phi        = input_background[sample_index][i]->GetLeaf("Electron_phi")->GetValue(lepInd1);
                                lep2_pt         = input_background[sample_index][i]->GetLeaf("Electron_pt")->GetValue(lepInd2);
                                lep2_eta        = input_background[sample_index][i]->GetLeaf("Electron_eta")->GetValue(lepInd2);
                                lep2_mass       = input_background[sample_index][i]->GetLeaf("Electron_mass")->GetValue(lepInd2);
                                lep2_phi        = input_background[sample_index][i]->GetLeaf("Electron_phi")->GetValue(lepInd2);
                              }

                              if (isZmm==1){
                                lep1_pt         = input_background[sample_index][i]->GetLeaf("Muon_pt")->GetValue(lepInd1);
                                lep1_eta        = input_background[sample_index][i]->GetLeaf("Muon_eta")->GetValue(lepInd1);
                                lep1_mass       = input_background[sample_index][i]->GetLeaf("Muon_mass")->GetValue(lepInd1);
                                lep1_phi        = input_background[sample_index][i]->GetLeaf("Muon_phi")->GetValue(lepInd1);
                                lep2_pt         = input_background[sample_index][i]->GetLeaf("Muon_pt")->GetValue(lepInd2);
                                lep2_eta        = input_background[sample_index][i]->GetLeaf("Muon_eta")->GetValue(lepInd2);
                                lep2_mass       = input_background[sample_index][i]->GetLeaf("Muon_mass")->GetValue(lepInd2);
                                lep2_phi        = input_background[sample_index][i]->GetLeaf("Muon_phi")->GetValue(lepInd2);
                              }

                              for (iJet=0; iJet<nJet; iJet++){
                                Jet_pt = input_background[sample_index][i]->GetLeaf("Jet_Pt")->GetValue(iJet);
                                if (Jet_pt > 25){
                                  Sum_Pt = Sum_Pt + Jet_pt;
                                 }
                              }

                              fprintf(log,"\n");

                              data -> Fill();
                            }
                          Sum_Pt = 0;

                        }

                      input_BR[sample_index][i]->Close();

                      i++;
                      file.close();
                      nextfile.close();
                      secnextfile.close();
                    }

                  skimmed -> cd ();
                  data    -> Write();
                  skimmed -> Close();
                }
                sample_index ++;
    }

  fclose(log);

                  
