//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <jpeg.hpp>
#include <Graphics.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TImage *Pitch;
        TImage *Ball;
        TImage *PolandPaddle;
        TImage *UkrainePaddle;
        TImage *ScorePanel;
        TLabel *PolandScore;
        TLabel *UkraineScore;
        TLabel *Label3;
        TTimer *BallTimer;
        TTimer *PolandPaddleUpTimer;
        TTimer *PolandPaddleDownTimer;
        TTimer *UkrainePaddleUpTimer;
        TTimer *UkrainePaddleDownTimer;
        TLabel *Title;
        TLabel *NewGameLabel;
        TLabel *EndGameLabel;
        TLabel *RulesLabel;
        TLabel *OptionsLabel;
        TLabel *PaddleSizeLabel;
        TLabel *BigPaddleLabel;
        TLabel *SmallPaddleLabel;
        TImage *Obstacle1;
        TImage *Obstacle2;
        TLabel *ObstacleLabel;
        TLabel *YesLabel;
        TLabel *NoLabel;
        TTimer *ObstacleTimer;
        TTimer *IsBumpedOffTimer;
        void __fastcall BallTimerTimer(TObject *Sender);
        void __fastcall PolandPaddleUpTimerTimer(TObject *Sender);
        void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall FormKeyUp(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall PolandPaddleDownTimerTimer(TObject *Sender);
        void __fastcall UkrainePaddleUpTimerTimer(TObject *Sender);
        void __fastcall UkrainePaddleDownTimerTimer(TObject *Sender);
        void __fastcall NewGameLabelClick(TObject *Sender);
        void __fastcall EndGameLabelClick(TObject *Sender);
        void __fastcall RulesLabelClick(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall OptionsLabelClick(TObject *Sender);
        void __fastcall BigPaddleLabelClick(TObject *Sender);
        void __fastcall SmallPaddleLabelClick(TObject *Sender);
        void __fastcall YesLabelClick(TObject *Sender);
        void __fastcall NoLabelClick(TObject *Sender);
        void __fastcall ObstacleTimerTimer(TObject *Sender);
        void __fastcall IsBumpedOffTimerTimer(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
