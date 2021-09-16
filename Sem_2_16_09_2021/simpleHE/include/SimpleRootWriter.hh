#ifndef SimpleRootWriter_H
#define SimpleRootWriter_H 1

#include "TTree.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TH3D.h"
#include "TFile.h"
#include <string>

class SimpleRootWriter{
  public:
    void Initialize(bool SaveTree=false);	
    void Fill();		// store an event
    void Finalize();	// write tree to a file
    static SimpleRootWriter* GetPointer(){
      if(pInstance==0) pInstance = new SimpleRootWriter();
      return pInstance;
    };

  private:
    SimpleRootWriter(){fSaveTree = false;};	// empty constructor
    static SimpleRootWriter* pInstance;

    bool fSaveTree;

  public:

    TH1F*  h1[500];
    TH2F*  h2[100];
     
    TTree* tree;

  private:
    TFile* file;
};

#endif
