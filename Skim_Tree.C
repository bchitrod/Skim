#include "lester_mt2_bisect.h"
void Skim_Tree()
{
  cout<<2<<endl;
  char sample[100];
  ifstream        sample_list;
  sample_list.open("sample1.txt");
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
		  int           Vtype;
		  int           isZee, isZmm;
		  float         ele1_pt, ele2_pt, muon1_pt, muon2_pt, jet1_pt, jet2_pt;
                  float         weight;
                  float         leadingJet_DeepFlavour;
                  float         leadingJet_bRegNNCorr;
                  float         leadingJet_e;
                  float         leadingJet_eta;
                  float         leadingJet_mass;
                  float         leadingJet_phi;
                  float         leadingJet_pt;
                  float         subleadingJet_DeepFlavour;
                  float         subleadingJet_bRegNNCorr;
                  float         subleadingJet_e;
                  float         subleadingJet_eta;
                  float         subleadingJet_mass;
                  float         subleadingJet_phi;
                  float         subleadingJet_pt;
                  float         ttH_sumET;
                  float         corrMET;
                  float         corrMETPhi;
                  float         MjjReg_phi12;
                  float         MjjReg_phi1M;
                  float         MjjReg_phi2M;
                  float         rho;
                  float         year;
                  float         bdt_MjjReg;
                  float         H_mass;
                  float         H_mass_noreg;

                  sprintf(skimmedfilename,"../skim_2018/skimmed_%s.root",sample);

                  TFile   *skimmed        = new TFile(skimmedfilename,"RECREATE");
                  TTree   *data           = new TTree("Events",   "Regression");

		  
                  data->Branch("weight", &weight, "weight/F");
		  data->Branch("leadingJet_pt", &leadingJet_pt, "leadingJet_pt/F");
                  data->Branch("leadingJet_eta", &leadingJet_eta, "leadingJet_eta/F");
                  data->Branch("leadingJet_mass", &leadingJet_mass, "leadingJet_mass/F");
                  data->Branch("leadingJet_phi", &leadingJet_phi, "leadingJet_phi/F");
		  data->Branch("leadingJet_e", &leadingJet_e, "leadingJet_e/F");
                  data->Branch("leadingJet_DeepFlavour", &leadingJet_DeepFlavour, "leadingJet_DeepFlavour/F");
		  data->Branch("leadingJet_bRegNNCorr", &leadingJet_bRegNNCorr, "leadingJet_bRegNNCorr/F");
		  data->Branch("subleadingJet_pt", &subleadingJet_pt, "subleadingJet_pt/F");
                  data->Branch("subleadingJet_eta", &subleadingJet_eta, "subleadingJet_eta/F");
                  data->Branch("subleadingJet_mass", &subleadingJet_mass, "subleadingJet_mass/F");
                  data->Branch("subleadingJet_phi", &subleadingJet_phi, "subleadingJet_phi/F");
                  data->Branch("subleadingJet_DeepFlavour", &subleadingJet_DeepFlavour, "subleadingJet_DeepFlavour/F");
		  data->Branch("subleadingJet_e", &subleadingJet_e, "subleadingJet_e/F");
		  data->Branch("corrMETPhi", &corrMETPhi, "corrMETPhi/F");
                  data->Branch("corrMET", &corrMET, "corrMET/F");
		  data->Branch("H_mass", &H_mass, "H_mass/F");
                  data->Branch("H_mass_noreg", &H_mass_noreg, "H_mass_noreg/F");
		  data->Branch("MjjReg_phi12", &MjjReg_phi12, "MjjReg_phi12/F");
                  data->Branch("MjjReg_phi1M", &MjjReg_phi1M, "MjjReg_phi1M/F");
                  data->Branch("MjjReg_phi2M", &MjjReg_phi2M, "MjjReg_phi2M/F");
                  data->Branch("ttH_sumET", &ttH_sumET, "ttH_sumET/F");
                  data->Branch("year", &year, "year/F");
		  data->Branch("Vtype", &Vtype, "Vtype/I");
                  data->Branch("rho", &rho, "rho/F");

                  while(1)
                    {
                      char filename[200],nextfilename[200],secnextfilename[200];

                      sprintf(filename,"/eos/user/b/bchitrod/VHbbAnalysisNtuples/Regression_2018/%s/output_%s_%d.root",sample,sample,i);
                      ifstream    file,nextfile,secnextfile;
                      file.open(filename);
                      sprintf(nextfilename,"/eos/user/b/bchitrod/VHbbAnalysisNtuples/Regression_2018/%s/output_%s_%d.root",sample,sample,i+1);
                      nextfile.open(nextfilename);
                      sprintf(secnextfilename,"/eos/user/b/bchitrod/VHbbAnalysisNtuples/Regression_2018/%s/output_%s_%d.root",sample,sample,i+2);
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
			  regression      = input_background[sample_index][i]->GetLeaf("regression")->GetValue();
			  isZee           = input_background[sample_index][i]->GetLeaf("isZee")->GetValue();
                          isZmm           = input_background[sample_index][i]->GetLeaf("isZmm")->GetValue();
			  ele1_pt         = input_background[sample_index][i]->GetLeaf("Electron_pt")->GetValue(lepInd1);
                          ele2_pt         = input_background[sample_index][i]->GetLeaf("Electron_pt")->GetValue(lepInd2);
                          muon1_pt        = input_background[sample_index][i]->GetLeaf("Muon_pt")->GetValue(lepInd1);
                          muon2_pt        = input_background[sample_index][i]->GetLeaf("Muon_pt")->GetValue(lepInd2);
                          jet1_pt         = input_background[sample_index][i]->GetLeaf("Jet_Pt")->GetValue(hJetInd1);
                          jet2_pt         = input_background[sample_index][i]->GetLeaf("Jet_Pt")->GetValue(hJetInd2);

			  if (regression==10 && jet1_pt>25 && jet2_pt>25)
                            {
			      if (isZee==1 && ele1_pt>25 && ele2_pt>25){
				weight                      = input_background[sample_index][i]->GetLeaf("weight")->GetValue();
				leadingJet_DeepFlavour      = input_background[sample_index][i]->GetLeaf("leadingJet_DeepFlavour")->GetValue();
				leadingJet_bRegNNCorr       = input_background[sample_index][i]->GetLeaf("leadingJet_bRegNNCorr")->GetValue();
				leadingJet_e                = input_background[sample_index][i]->GetLeaf("leadingJet_e")->GetValue();
				leadingJet_eta              = input_background[sample_index][i]->GetLeaf("leadingJet_eta")->GetValue();
				leadingJet_mass             = input_background[sample_index][i]->GetLeaf("leadingJet_mass")->GetValue();
				leadingJet_phi              = input_background[sample_index][i]->GetLeaf("leadingJet_phi")->GetValue();
				leadingJet_pt               = input_background[sample_index][i]->GetLeaf("leadingJet_pt")->GetValue();
				subleadingJet_DeepFlavour   = input_background[sample_index][i]->GetLeaf("subleadingJet_DeepFlavour")->GetValue();
				subleadingJet_bRegNNCorr    = input_background[sample_index][i]->GetLeaf("subleadingJet_bRegNNCorr")->GetValue();
				subleadingJet_e             = input_background[sample_index][i]->GetLeaf("subleadingJet_e")->GetValue();
				subleadingJet_eta           = input_background[sample_index][i]->GetLeaf("subleadingJet_eta")->GetValue();
				subleadingJet_mass          = input_background[sample_index][i]->GetLeaf("subleadingJet_mass")->GetValue();
				subleadingJet_phi           = input_background[sample_index][i]->GetLeaf("subleadingJet_phi")->GetValue();
				subleadingJet_pt            = input_background[sample_index][i]->GetLeaf("subleadingJet_pt")->GetValue();
				ttH_sumET                   = input_background[sample_index][i]->GetLeaf("ttH_sumET")->GetValue();
				corrMET                     = input_background[sample_index][i]->GetLeaf("corrMET")->GetValue();
				corrMETPhi                  = input_background[sample_index][i]->GetLeaf("corrMETPhi")->GetValue();
				MjjReg_phi12                = input_background[sample_index][i]->GetLeaf("MjjReg_phi12")->GetValue();
				MjjReg_phi1M                = input_background[sample_index][i]->GetLeaf("MjjReg_phi1M")->GetValue();
				MjjReg_phi2M                = input_background[sample_index][i]->GetLeaf("MjjReg_phi2M")->GetValue();
				rho                         = input_background[sample_index][i]->GetLeaf("rho")->GetValue();
				year                        = input_background[sample_index][i]->GetLeaf("year")->GetValue();
				bdt_MjjReg                  = input_background[sample_index][i]->GetLeaf("bdt_MjjReg")->GetValue();
				H_mass                      = input_background[sample_index][i]->GetLeaf("H_mass")->GetValue();
				H_mass_noreg                = input_background[sample_index][i]->GetLeaf("H_mass_noreg")->GetValue();
			      }
			      
			      else if (muon1_pt>25 && muon2_pt>25 && isZmm==1){
				weight                      = input_background[sample_index][i]->GetLeaf("weight")->GetValue();
                                leadingJet_DeepFlavour      = input_background[sample_index][i]->GetLeaf("leadingJet_DeepFlavour")->GetValue();
                                leadingJet_bRegNNCorr       = input_background[sample_index][i]->GetLeaf("leadingJet_bRegNNCorr")->GetValue();
                                leadingJet_e                = input_background[sample_index][i]->GetLeaf("leadingJet_e")->GetValue();
                                leadingJet_eta              = input_background[sample_index][i]->GetLeaf("leadingJet_eta")->GetValue();
                                leadingJet_mass             = input_background[sample_index][i]->GetLeaf("leadingJet_mass")->GetValue();
                                leadingJet_phi              = input_background[sample_index][i]->GetLeaf("leadingJet_phi")->GetValue();
                                leadingJet_pt               = input_background[sample_index][i]->GetLeaf("leadingJet_pt")->GetValue();
                                subleadingJet_DeepFlavour   = input_background[sample_index][i]->GetLeaf("subleadingJet_DeepFlavour")->GetValue();
                                subleadingJet_bRegNNCorr    = input_background[sample_index][i]->GetLeaf("subleadingJet_bRegNNCorr")->GetValue();
                                subleadingJet_e             = input_background[sample_index][i]->GetLeaf("subleadingJet_e")->GetValue();
                                subleadingJet_eta           = input_background[sample_index][i]->GetLeaf("subleadingJet_eta")->GetValue();
                                subleadingJet_mass          = input_background[sample_index][i]->GetLeaf("subleadingJet_mass")->GetValue();
                                subleadingJet_phi           = input_background[sample_index][i]->GetLeaf("subleadingJet_phi")->GetValue();
                                subleadingJet_pt            = input_background[sample_index][i]->GetLeaf("subleadingJet_pt")->GetValue();
                                ttH_sumET                   = input_background[sample_index][i]->GetLeaf("ttH_sumET")->GetValue();
                                corrMET                     = input_background[sample_index][i]->GetLeaf("corrMET")->GetValue();
                                corrMETPhi                  = input_background[sample_index][i]->GetLeaf("corrMETPhi")->GetValue();
                                MjjReg_phi12                = input_background[sample_index][i]->GetLeaf("MjjReg_phi12")->GetValue();
                                MjjReg_phi1M                = input_background[sample_index][i]->GetLeaf("MjjReg_phi1M")->GetValue();
				MjjReg_phi2M                = input_background[sample_index][i]->GetLeaf("MjjReg_phi2M")->GetValue();
                                rho                         = input_background[sample_index][i]->GetLeaf("rho")->GetValue();
                                year                        = input_background[sample_index][i]->GetLeaf("year")->GetValue();
                                bdt_MjjReg                  = input_background[sample_index][i]->GetLeaf("bdt_MjjReg")->GetValue();
                                H_mass                      = input_background[sample_index][i]->GetLeaf("H_mass")->GetValue();
                                H_mass_noreg                = input_background[sample_index][i]->GetLeaf("H_mass_noreg")->GetValue();
			      }
			      fprintf(log,"\n");
			      data -> Fill();
			    }
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
  
}                  
