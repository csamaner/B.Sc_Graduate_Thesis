{


    TFile * rootfile = new TFile( "Hadd_C_Combined.root", "READ" );

    //-----------------------------------------------------------------------------------------
    // RATIO 32 -----------------------------------------------------------------------
    //-----------------------------------------------------------------------------------------


    TH1F * Njet2 = (TH1F*)rootfile->Get("hist_jets_no_2_HT");
    TH1F * Njet3 = (TH1F*)rootfile->Get("hist_jets_no_3_HT");

    TCanvas *canvas_R32 = new TCanvas("Ratio32","Ratio of 2 to 3",0,0,1200,1200);
    canvas_R32->SetFillColor(41);
    canvas_R32->Divide(1,2);
    canvas_R32->cd(1);

        gPad->SetGrid();
        gPad->SetLogy();
        gPad->SetLogx();
        Njet2->SetMarkerStyle(20);
        Njet2->SetMarkerColor(kRed);
        Njet2->GetXaxis()->SetRangeUser(100, 2000);
        Njet2->SetMinimum(1);
        Njet2->SetTitle("HT distribution of nJet2 and nJet3");
        Njet2->GetXaxis()->SetTitle("HT (GeV)");
        Njet2->Draw("E1");
        Njet3->SetMarkerStyle(24);
        Njet3->SetMarkerColor(kBlue);
        Njet3->Draw("SAME E1");

    canvas_R32->cd(2);

        gPad->SetGrid();
        TH1F *hist_Ratio32 = (TH1F*)Njet3->Clone("hist_Ratio32");
        hist_Ratio32->SetLineColor(kBlack);
        hist_Ratio32->SetMinimum(0.0);
        hist_Ratio32->SetMaximum(1.2);
        hist_Ratio32->GetXaxis()->SetRangeUser(0, 2000);
        hist_Ratio32->Divide(Njet2);
        hist_Ratio32->SetMarkerStyle(21);
        hist_Ratio32->SetTitle("Ratio of Njets>3 over Njets>2");
        hist_Ratio32->GetXaxis()->SetTitle("HT (GeV)");
        hist_Ratio32->GetYaxis()->SetTitle("Ratio32");
        hist_Ratio32->Draw();

    canvas_R32->Print("Tez_Eps_Files/Raito32.eps");

    //-----------------------------------------------------------------------------------------
    //PT Resolution ------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------------

    //Leading Jet


    TH2F *hist_PT_RESO[0] = (TH2F*)rootfile->Get("LeadingJetPtReso");

    TCanvas * canvas_PT_reso1 = new TCanvas("Pt_Reso_LeadingJet","PT Resolution of Leading Jet",0,0,1200,1200);

    canvas_PT_reso1->SetFillColor(41);
    canvas_PT_reso1->Divide(1,2);
    canvas_PT_reso1->cd(1);

        hist_PT_RESO[0]->SetTitle("Pt Resolution of the Leading Jet");
        hist_PT_RESO[0]->GetXaxis()->SetTitle("PT of the Leading jet");
        hist_PT_RESO[0]->GetYaxis()->SetTitle("Resolution");
        hist_PT_RESO[0]->Draw("COLZ");

    canvas_PT_reso1->cd(2);

        TProfile *hist_PT_Prof[0] = hist_PT_RESO[0]->ProfileX();
        hist_PT_Prof[0]->SetMinimum(0);
        hist_PT_Prof[0]->SetMaximum(0.5);
        hist_PT_Prof[0]->SetTitle("Pt Resolution of the Leading Jet (Profile)");
        hist_PT_Prof[0]->GetXaxis()->SetTitle("PT of the Leading jet");
        hist_PT_Prof[0]->GetYaxis()->SetTitle("Resolution");
        hist_PT_Prof[0]->Draw("][ hist ");

    canvas_PT_reso1->Print("Tez_Eps_Files/PtResoLeadingJet.eps");

    //Second Jet

    TH2F *hist_PT_RESO[1] = (TH2F*)rootfile->Get("SecondJetPtReso");

    TCanvas * canvas_PT_reso2 = new TCanvas("Pt_Reso_SecondJet","PT Resolution of Second Jet",0,0,1200,1200);

    canvas_PT_reso2->SetFillColor(41);
    canvas_PT_reso2->Divide(1,2);
    canvas_PT_reso2->cd(1);

        hist_PT_RESO[1]->SetTitle("Pt Resolution of the Second Jet");
        hist_PT_RESO[1]->GetXaxis()->SetTitle("PT of the Second jet");
        hist_PT_RESO[1]->GetYaxis()->SetTitle("Resolution");
        hist_PT_RESO[1]->Draw("COLZ");

    canvas_PT_reso2->cd(2);

        TProfile *hist_PT_Prof[1] = hist_PT_RESO[1]->ProfileX();
        hist_PT_Prof[1]->SetMinimum(0);
        hist_PT_Prof[1]->SetMaximum(0.5);
        hist_PT_Prof[1]->SetTitle("Pt Resolution of the Second Jet (Profile)");
        hist_PT_Prof[1]->GetXaxis()->SetTitle("PT of the Second jet");
        hist_PT_Prof[1]->GetYaxis()->SetTitle("Resolution");
        hist_PT_Prof[1]->Draw("][ hist ");

    canvas_PT_reso2->Print("Tez_Eps_Files/PtResoSecondJet.eps");

    // Third Jet

    TH2F *hist_PT_RESO[2] = (TH2F*)rootfile->Get("ThirdJetPtReso");

    TCanvas * canvas_PT_reso3 = new TCanvas("Pt_Reso_ThirdJet","PT Resolution of Third Jet",0,0,1200,1200);

    canvas_PT_reso3->SetFillColor(41);
    canvas_PT_reso3->Divide(1,2);
    canvas_PT_reso3->cd(1);

        hist_PT_RESO[2]->SetTitle("Pt Resolution of the Third Jet");
        hist_PT_RESO[2]->GetXaxis()->SetTitle("PT of the Third jet");
        hist_PT_RESO[2]->GetYaxis()->SetTitle("Resolution");
        hist_PT_RESO[2]->Draw("COLZ");

    canvas_PT_reso3->cd(2);

        TProfile *hist_PT_Prof[2] = hist_PT_RESO[2]->ProfileX();
        hist_PT_Prof[2]->SetMinimum(0);
        hist_PT_Prof[2]->SetMaximum(0.5);
        hist_PT_Prof[2]->SetTitle("Pt Resolution of the Third Jet (Profile)");
        hist_PT_Prof[2]->GetXaxis()->SetTitle("PT of the Third jet");
        hist_PT_Prof[2]->GetYaxis()->SetTitle("Resolution");
        hist_PT_Prof[2]->Draw("][ hist ");

    canvas_PT_reso3->Print("Tez_Eps_Files/PtResoThirdJet.eps");


    //-----------------------------------------------------------------------------------------
    // Rapidity Resolution --------------------------------------------------------------------
    //-----------------------------------------------------------------------------------------

    // Rapidity Resolution for 60 - 100 GeV


    TH2F *hist_rapi_reso[0] = (TH2F*)rootfile->Get("rapiReso60-100");

    TCanvas * canvas_rapi_reso[0] = new TCanvas("rapiReso60-100","Rapidity Resolution for 60-100 GeV",0,0,800,1200);

    canvas_rapi_reso[0]->SetFillColor(41);
    canvas_rapi_reso[0]->Divide(1,3);
    canvas_rapi_reso[0]->cd(1);

        hist_rapi_reso[0]->GetXaxis()->SetTitle("Ygen");
        hist_rapi_reso[0]->GetYaxis()->SetTitle("Ygen-Ycalo");
        hist_rapi_reso[0]->Draw("cont");

    canvas_rapi_reso[0]->cd(2);

        TProfile *hist_Rapi_Prof[0] = hist_rapi_reso[0]->ProfileX();
        hist_Rapi_Prof[0]->SetMinimum(-0.1);
        hist_Rapi_Prof[0]->SetMaximum(0.1);
        hist_Rapi_Prof[0]->SetTitle("Profile");
        hist_Rapi_Prof[0]->GetXaxis()->SetTitle("Ygen");
        hist_Rapi_Prof[0]->GetYaxis()->SetTitle("Ygen-Ycalo");
        hist_Rapi_Prof[0]->Draw("E1");

    canvas_rapi_reso[0]->cd(3);

//        gStyle->SetOptStat(1111);
        gStyle->SetOptFit(0111);
        TH1D * projRapiY[0] = hist_rapi_reso[0]->ProjectionY();
        projRapiY[0]->SetFillColor(kCyan-3);
        TF1 *fitProjectionRapi[0] = new TF1("fitProjectionRapi[0]","gaus",-0.4,0.4);
        projRapiY[0]->Fit("fitProjectionRapi[0]","","",-0.4,0.4);
        projRapiY[0]->SetMinimum(0);
        projRapiY[0]->GetXaxis()->SetRangeUser(-0.3, 0.3);
        projRapiY[0]->SetTitle("Ygen-Ycalo projection fitted to gaussian");
        projRapiY[0]->GetXaxis()->SetTitle("Ygen-Ycalo");
        projRapiY[0]->GetYaxis()->SetTitle("Events");
        projRapiY[0]->Draw();


    canvas_rapi_reso[0]->Print("Tez_Eps_Files/rapiReso60-100.eps");

    // Rapidity Resolution for 100 - 150 GeV


    TH2F *hist_rapi_reso[1] = (TH2F*)rootfile->Get("rapiReso100-150");

    TCanvas * canvas_rapi_reso[1] = new TCanvas("rapiReso100-150","Rapidity Resolution for 100-150 GeV",0,0,800,1200);

    canvas_rapi_reso[1]->SetFillColor(41);
    canvas_rapi_reso[1]->Divide(1,3);
    canvas_rapi_reso[1]->cd(1);

        hist_rapi_reso[1]->GetXaxis()->SetTitle("Ygen");
        hist_rapi_reso[1]->GetYaxis()->SetTitle("Ygen-Ycalo");
        hist_rapi_reso[1]->Draw("cont");

    canvas_rapi_reso[1]->cd(2);

        TProfile *hist_Rapi_Prof[1] = hist_rapi_reso[1]->ProfileX();
        hist_Rapi_Prof[1]->SetMinimum(-0.1);
        hist_Rapi_Prof[1]->SetMaximum(0.1);
        hist_Rapi_Prof[1]->SetTitle("Profile");
        hist_Rapi_Prof[1]->GetXaxis()->SetTitle("Ygen");
        hist_Rapi_Prof[1]->GetYaxis()->SetTitle("Ygen-Ycalo");
        hist_Rapi_Prof[1]->Draw("E1");

    canvas_rapi_reso[1]->cd(3);

//        gStyle->SetOptStat(1111);
        gStyle->SetOptFit(0111);
        TH1D * projRapiY[1] = hist_rapi_reso[1]->ProjectionY();
        projRapiY[1]->SetFillColor(kCyan-3);
        TF1 *fitProjectionRapi[0] = new TF1("fitProjectionRapi[0]","gaus",-0.4,0.4);
        projRapiY[1]->Fit("fitProjectionRapi[0]","","",-0.4,0.4);
        projRapiY[1]->SetMinimum(0);
        projRapiY[1]->GetXaxis()->SetRangeUser(-0.3, 0.3);
        projRapiY[1]->SetTitle("Ygen-Ycalo projection fitted to gaussian");
        projRapiY[1]->GetXaxis()->SetTitle("Ygen-Ycalo");
        projRapiY[1]->GetYaxis()->SetTitle("Events");
        projRapiY[1]->Draw();


    canvas_rapi_reso[1]->Print("Tez_Eps_Files/rapiReso100-150.eps");

    // Rapidity Resolution for 150 - 200 GeV

        TH2F *hist_rapi_reso[2] = (TH2F*)rootfile->Get("rapiReso150-200");

        TCanvas * canvas_rapi_reso[2] = new TCanvas("rapiReso150-200","Rapidity Resolution for 150-200 GeV",0,0,800,1200);

        canvas_rapi_reso[2]->SetFillColor(41);
        canvas_rapi_reso[2]->Divide(1,3);
        canvas_rapi_reso[2]->cd(1);

            hist_rapi_reso[2]->GetXaxis()->SetTitle("Ygen");
            hist_rapi_reso[2]->GetYaxis()->SetTitle("Ygen-Ycalo");
            hist_rapi_reso[2]->Draw("cont");

        canvas_rapi_reso[2]->cd(2);

            TProfile *hist_Rapi_Prof[2] = hist_rapi_reso[2]->ProfileX();
            hist_Rapi_Prof[2]->SetMinimum(-0.1);
            hist_Rapi_Prof[2]->SetMaximum(0.1);
            hist_Rapi_Prof[2]->SetTitle("Profile");
            hist_Rapi_Prof[2]->GetXaxis()->SetTitle("Ygen");
            hist_Rapi_Prof[2]->GetYaxis()->SetTitle("Ygen-Ycalo");
            hist_Rapi_Prof[2]->Draw("E1");

        canvas_rapi_reso[2]->cd(3);

    //        gStyle->SetOptStat(1111);
            gStyle->SetOptFit(0111);
            TH1D * projRapiY[2] = hist_rapi_reso[2]->ProjectionY();
            projRapiY[2]->SetFillColor(kCyan-3);
            TF1 *fitProjectionRapi[0] = new TF1("fitProjectionRapi[0]","gaus",-0.4,0.4);
            projRapiY[2]->Fit("fitProjectionRapi[0]","","",-0.4,0.4);
            projRapiY[2]->SetMinimum(0);
            projRapiY[2]->GetXaxis()->SetRangeUser(-0.3, 0.3);
            projRapiY[2]->SetTitle("Ygen-Ycalo projection fitted to gaussian");
            projRapiY[2]->GetXaxis()->SetTitle("Ygen-Ycalo");
            projRapiY[2]->GetYaxis()->SetTitle("Events");
            projRapiY[2]->Draw();


        canvas_rapi_reso[2]->Print("Tez_Eps_Files/rapiReso150-200.eps");











}
