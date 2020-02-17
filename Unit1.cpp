//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "mmsystem.h"
#include "Unit1.h"
#include "Unit2.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;

int x = -8, y = -8, y1 = -8, y2 = 8;
int PaddleMove = 8;
int scorePL = 0, scoreUKR = 0;
bool isBumpedOff = false;

void StartGame()
{
        //PolandPaddle's starting position
        Form1 -> ObstacleTimer -> Enabled = true;
        Form1 -> PolandPaddle -> Top = Form1 -> Pitch -> Height /2 +
        Form1 -> ScorePanel -> Height - Form1 -> PolandPaddle -> Height / 2;

        //UkrainePaddle's starting position
        Form1 -> UkrainePaddle -> Top = Form1 -> Pitch -> Height /2 +
        Form1 -> ScorePanel -> Height - Form1 -> UkrainePaddle -> Height / 2;

        if (y > 0)
                y = 8;
        else
                y = -8;

        //Ball's starting position
        Form1 -> Ball -> Top = Form1 -> Pitch -> Height / 2 +
        Form1 -> ScorePanel -> Height - Form1 -> Ball -> Height / 2;
        Form1 -> Ball -> Left = Form1 -> Pitch -> Width /2 - Form1 -> Ball -> Width / 2;

        sndPlaySound("snd/whistle_short.wav", SND_ASYNC);
        Application -> ProcessMessages();
        Sleep(500);

        //reset Ball's move speed
        Form1 -> BallTimer -> Interval = 30;
        Form1 -> BallTimer -> Enabled = true;

        Form1 -> PolandPaddleUpTimer -> Enabled = false;
        Form1 -> PolandPaddleDownTimer -> Enabled = false;
        Form1 -> UkrainePaddleUpTimer -> Enabled = false;
        Form1 -> UkrainePaddleDownTimer -> Enabled = false;
}

void ResetGame()
{
        //reset scores
        scorePL = 0;
        scoreUKR = 0;
        Form1 -> PolandScore -> Caption = IntToStr(scorePL);
        Form1 -> UkraineScore -> Caption = IntToStr(scoreUKR);

        //display main menu labels
        Form1 -> Title -> Visible = true;
        Form1 -> NewGameLabel -> Visible = true;
        Form1 -> OptionsLabel -> Visible = true;
        Form1 -> RulesLabel -> Visible = true;
        Form1 -> EndGameLabel -> Visible = true;

        //reset Ball's position and move direction
        Form1 -> Ball -> Top = Form1 -> Pitch -> Height / 2 +
        Form1 -> ScorePanel -> Height - Form1 -> Ball -> Height / 2;
        Form1 -> Ball -> Left = Form1 -> Pitch -> Width /2 - Form1 -> Ball -> Width / 2;

        x = -8;
        y = -8;

        //reset obstacles position and move direction
        Form1 -> Obstacle1 -> Top = Form1 -> Pitch -> Top +
        Form1 -> Pitch -> Height - 40 - Form1 -> Obstacle1 -> Height;
        Form1 -> Obstacle2 -> Top = Form1 -> Pitch -> Top + 40;
        Form1 -> ObstacleTimer -> Enabled = false;

        y1 = -8;
        y2 = 8;
}

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm1::BallTimerTimer(TObject *Sender)
{
        Ball -> Left += x;
        Ball -> Top += y;

        //change Ball's direction after bounce off the wall
        if (Ball -> Top <= Pitch -> Top)
        {
                y = -y;
                sndPlaySound("snd/hit.wav", SND_ASYNC);
        }
        if (Ball -> Top + Ball -> Height >= Pitch -> Top + Pitch -> Height)
        {
                y = -y;
                sndPlaySound("snd/hit.wav", SND_ASYNC);
        }

        //change Ball's 'x' direction after bounce off the PolandPaddle
        if (Ball -> Left <= PolandPaddle -> Left + PolandPaddle -> Width &&
            Ball -> Left >= (PolandPaddle -> Left + PolandPaddle -> Width) - abs(x) &&
            Ball -> Top + (3 * Ball -> Height) / 4 >= PolandPaddle -> Top &&
            Ball -> Top + Ball -> Height / 4 <= PolandPaddle -> Top + PolandPaddle -> Height &&
            isBumpedOff == false)
            {
                if (PolandPaddleUpTimer -> Enabled)
                        y -= 2;
                else if (PolandPaddleDownTimer -> Enabled)
                                y += 2;

                x = -x;
                sndPlaySound("snd/hit.wav", SND_ASYNC);
                if (BallTimer -> Interval > 2)
                        BallTimer -> Interval -= 2;

                isBumpedOff = true;
                IsBumpedOffTimer -> Enabled = true;
            }

        //change Ball's 'x' direction after bounce off the UkrainePaddle
        if (Ball -> Left + Ball -> Width >= UkrainePaddle -> Left &&
            Ball -> Left + Ball -> Width <= UkrainePaddle -> Left + abs(x) &&
            Ball -> Top + (3 * Ball -> Height) / 4 >= UkrainePaddle -> Top &&
            Ball -> Top + Ball -> Height / 4 <= UkrainePaddle -> Top + UkrainePaddle -> Height &&
            isBumpedOff == false)
            {
                if (UkrainePaddleUpTimer -> Enabled)
                                y -= 2;
                else if (UkrainePaddleDownTimer -> Enabled)
                                y += 2;

                x = -x;
                sndPlaySound("snd/hit.wav", SND_ASYNC);
                if (BallTimer -> Interval > 2)
                        BallTimer -> Interval -= 2;

                isBumpedOff = true;
                IsBumpedOffTimer -> Enabled = true;
            }

        //PolandPaddle's goal
        if (Ball -> Left + Ball -> Width >= Pitch -> Left + Pitch -> Width)
                {
                        BallTimer -> Enabled = false;
                        scorePL++;
                        PolandScore -> Caption = IntToStr(scorePL);
                        if (scorePL == 10)
                        {
                                sndPlaySound("snd/win_cheer.wav", SND_ASYNC);
                                Application -> MessageBox("Zwyciêstwo! Polska mistrzem Europy!",
                                "Koniec meczu!", NULL);
                                ResetGame();
                        }
                        else
                        {
                                sndPlaySound("snd/goal_claps.wav", SND_ASYNC);
                                Application -> MessageBox("Punkt dla Polski", "GOOOL!!", NULL);
                                StartGame();
                        }
                }

        //UkrainePaddle's goal
        if (Ball -> Left <= Pitch -> Left)
                {
                        BallTimer -> Enabled = false;
                        scoreUKR++;
                        UkraineScore -> Caption = IntToStr(scoreUKR);
                        if (scoreUKR == 10)
                        {
                                sndPlaySound("snd/loose_boo.wav", SND_ASYNC);
                                Application -> MessageBox("Przegrana! Ukraina pokona³a Polskê!",
                                "Koniec meczu!", NULL);
                                ResetGame();
                        }
                        else
                        {
                                sndPlaySound("snd/goal_boo.wav", SND_ASYNC);
                                Application -> MessageBox("Punkt dla Ukrainy", "GOOOL!!", NULL);
                                StartGame();
                        }
                }

        //change Ball's 'y' direction after bounce off the top of PolandPaddle
        if (Ball -> Left + (3 * Ball -> Width) / 4 >= PolandPaddle -> Left &&
            Ball -> Left + Ball -> Width / 4 <= PolandPaddle -> Left + PolandPaddle -> Width &&
            Ball -> Top + Ball -> Height >= PolandPaddle -> Top &&
            Ball -> Top + Ball -> Height <= PolandPaddle -> Top + abs(y) &&
            isBumpedOff == false)
            {
                y = -y;
                isBumpedOff = true;
                IsBumpedOffTimer -> Enabled = true;
                sndPlaySound("snd/hit.wav", SND_ASYNC);
            }

        //change Ball's 'y' direction after bounce off the top of UkrainePaddle
        if (Ball -> Left + (3 * Ball -> Width) / 4 >= UkrainePaddle -> Left &&
            Ball -> Left + Ball -> Width / 4 <= UkrainePaddle -> Left + UkrainePaddle -> Width &&
            Ball -> Top + Ball -> Height >= UkrainePaddle -> Top &&
            Ball -> Top + Ball -> Height <= UkrainePaddle -> Top + abs(y) &&
            isBumpedOff == false)
            {
                y = -y;
                isBumpedOff = true;
                IsBumpedOffTimer -> Enabled = true;
                sndPlaySound("snd/hit.wav", SND_ASYNC);
            }

        //change Ball's 'y' direction after bounce off the bottom of PolandPaddle
        if (Ball -> Left + (3 * Ball -> Width) / 4 >= PolandPaddle -> Left &&
            Ball -> Left + Ball -> Width / 4 <= PolandPaddle -> Left + PolandPaddle -> Width &&
            Ball -> Top <= PolandPaddle -> Top + PolandPaddle -> Height &&
            Ball -> Top >= PolandPaddle -> Top + PolandPaddle -> Height - abs(y)
            && isBumpedOff == false)
            {
                y = -y;
                isBumpedOff = true;
                IsBumpedOffTimer -> Enabled = true;
                sndPlaySound("snd/hit.wav", SND_ASYNC);
            }

        //change Ball's 'y' direction after bounce off the bottom of UkrainePaddle
        if (Ball -> Left + (3 * Ball -> Width) / 4 >= UkrainePaddle -> Left &&
            Ball -> Left + Ball -> Width / 4 <= UkrainePaddle -> Left + UkrainePaddle -> Width &&
            Ball -> Top <= UkrainePaddle -> Top + UkrainePaddle -> Height &&
            Ball -> Top >= UkrainePaddle -> Top + UkrainePaddle -> Height - abs(y)
            && isBumpedOff == false)
            {
                y = -y;
                isBumpedOff = true;
                IsBumpedOffTimer -> Enabled = true;
                sndPlaySound("snd/hit.wav", SND_ASYNC);
            }

        //Change Ball's 'x' direction after bounce off Obstacle1's left and right edge
        if (Ball -> Left + Ball -> Width >= Obstacle1 -> Left &&
            Ball -> Left <= Obstacle1 -> Left + Obstacle1 -> Width &&
            Ball -> Top + (3 * Ball -> Height) / 4 >= Obstacle1 -> Top &&
            Ball -> Top + Ball -> Height / 4 <= Obstacle1 -> Top + Obstacle1 -> Height &&
            Obstacle1 -> Visible == true && isBumpedOff == false)
            {
                x = -x;
                isBumpedOff = true;
                IsBumpedOffTimer -> Enabled = true;
                sndPlaySound("snd/hit.wav", SND_ASYNC);
            }

        //Change Ball's 'x' direction after bounce off Obstacle2's left and right edge
        if (Ball -> Left + Ball -> Width >= Obstacle2 -> Left &&
            Ball -> Left <= Obstacle2 -> Left + Obstacle2 -> Width &&
            Ball -> Top + (3 * Ball -> Height) / 4 >= Obstacle2 -> Top &&
            Ball -> Top + Ball -> Height / 4 <= Obstacle2 -> Top + Obstacle1 -> Height &&
            Obstacle2 -> Visible == true && isBumpedOff == false)
            {
                x = -x;
                isBumpedOff = true;
                IsBumpedOffTimer -> Enabled = true;
                sndPlaySound("snd/hit.wav", SND_ASYNC);
            }

        //Change Ball's 'x' direction after bounce off Obstacle1's top and bottom edge
        if (Ball -> Left + (3 * Ball -> Width) / 4 >= Obstacle1 -> Left &&
            Ball -> Left + Ball -> Width / 4 <= Obstacle1 -> Left + Obstacle1 -> Width &&
            Ball -> Top + Ball -> Height >= Obstacle1 -> Top &&
            Ball -> Top <= Obstacle1 -> Top + Obstacle1 -> Height &&
            Obstacle1 -> Visible == true && isBumpedOff == false)
            {
                y = -y;
                isBumpedOff = true;
                IsBumpedOffTimer -> Enabled = true;
                sndPlaySound("snd/hit.wav", SND_ASYNC);
            }

        //Change Ball's 'x' direction after bounce off Obstacle2's top and bottom edge
        if (Ball -> Left + (3 * Ball -> Width) / 4 >= Obstacle2 -> Left &&
            Ball -> Left + Ball -> Width / 4 <= Obstacle2 -> Left + Obstacle2 -> Width &&
            Ball -> Top + Ball -> Height >= Obstacle2 -> Top &&
            Ball -> Top <= Obstacle2 -> Top + Obstacle2 -> Height &&
            Obstacle2 -> Visible == true && isBumpedOff == false)
            {
                y = -y;
                isBumpedOff = true;
                IsBumpedOffTimer -> Enabled = true;
                sndPlaySound("snd/hit.wav", SND_ASYNC);
            }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::PolandPaddleUpTimerTimer(TObject *Sender)
{
        if (PolandPaddle -> Top >= Pitch -> Top + 2)
                PolandPaddle -> Top -= PaddleMove;
}
//---------------------------------------------------------------------------


void __fastcall TForm1::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
        if (Key == 0x41)
                PolandPaddleUpTimer -> Enabled = true;
        if (Key == 0x5A)
                PolandPaddleDownTimer -> Enabled = true;

        if (Key == VK_UP)
                UkrainePaddleUpTimer -> Enabled = true;
        if (Key == VK_DOWN)
                UkrainePaddleDownTimer -> Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormKeyUp(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
        if (Key == 0x41)
                PolandPaddleUpTimer -> Enabled = false;
        if (Key == 0x5A)
                PolandPaddleDownTimer -> Enabled = false;

        if (Key == VK_UP)
                UkrainePaddleUpTimer -> Enabled = false;
        if (Key == VK_DOWN)
                UkrainePaddleDownTimer -> Enabled = false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::PolandPaddleDownTimerTimer(TObject *Sender)
{
        if (PolandPaddle -> Top + PolandPaddle -> Height <= Pitch -> Top + Pitch -> Height - 2)
                PolandPaddle -> Top += PaddleMove;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::UkrainePaddleUpTimerTimer(TObject *Sender)
{
        if (UkrainePaddle -> Top >= Pitch -> Top + 2)
                UkrainePaddle -> Top -= PaddleMove;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::UkrainePaddleDownTimerTimer(TObject *Sender)
{
        if (UkrainePaddle -> Top + UkrainePaddle -> Height <= Pitch -> Top + Pitch -> Height - 2)
                UkrainePaddle -> Top += PaddleMove;
}
//---------------------------------------------------------------------------



void __fastcall TForm1::NewGameLabelClick(TObject *Sender)
{
        StartGame();
        Title -> Visible = false;
        NewGameLabel -> Visible = false;
        RulesLabel -> Visible = false;
        OptionsLabel -> Visible = false;
        EndGameLabel -> Visible = false;
        PaddleSizeLabel -> Visible = false;
        BigPaddleLabel -> Visible = false;
        SmallPaddleLabel -> Visible = false;
        ObstacleLabel -> Visible = false;
        YesLabel -> Visible = false;
        NoLabel -> Visible = false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::EndGameLabelClick(TObject *Sender)
{
        Application -> Terminate();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::RulesLabelClick(TObject *Sender)
{
        Form2 -> ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormCreate(TObject *Sender)
{
        AnsiString text1 = "Jesteœmy w alternatywnej rzeczywistoœci.";
        AnsiString text2 = "Jest rok 2012, w³aœnie trwa EURO 2012.";
        AnsiString text3 = "Gospodarze mistrzostw walcz¹ przeciwko sobie w meczu fina³owym.";
        AnsiString text4 = "PoprowadŸ nasz¹ reprezentacjê do zwyciêstwa!";
        AnsiString header = "Prolog";

        ShowMessage(text1 + sLineBreak + text2 + sLineBreak + text3 + sLineBreak + text4 + sLineBreak);


        Ball -> Top = Form1 -> Pitch -> Height / 2 +
        ScorePanel -> Height - Form1 -> Ball -> Height / 2;
        Ball -> Left = Form1 -> Pitch -> Width /2 - Form1 -> Ball -> Width / 2;

        Obstacle1 -> Top = Pitch -> Top + Pitch -> Height - 40 - Obstacle1 -> Height;
        Obstacle2 -> Top = Pitch -> Top + 40;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::OptionsLabelClick(TObject *Sender)
{
        PaddleSizeLabel -> Visible = true;
        BigPaddleLabel -> Visible = true;
        SmallPaddleLabel -> Visible = true;
        ObstacleLabel -> Visible = true;
        YesLabel -> Visible = true;
        NoLabel -> Visible = true;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::BigPaddleLabelClick(TObject *Sender)
{
        PolandPaddle -> Picture -> LoadFromFile("img/paddle_Poland.bmp");
        UkrainePaddle -> Picture -> LoadFromFile("img/paddle_Ukraine.bmp");
        PolandPaddle -> Top = Pitch -> Top + Pitch -> Height / 2 - PolandPaddle -> Height / 2;
        UkrainePaddle -> Top = Pitch -> Top + Pitch -> Height / 2 - UkrainePaddle -> Height / 2;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SmallPaddleLabelClick(TObject *Sender)
{
        PolandPaddle -> Picture -> LoadFromFile("img/paddle_Poland_small.bmp");
        UkrainePaddle -> Picture -> LoadFromFile("img/paddle_Ukraine_small.bmp");
        PolandPaddle -> Top = Pitch -> Top + Pitch -> Height / 2 - PolandPaddle -> Height / 2;
        UkrainePaddle -> Top = Pitch -> Top + Pitch -> Height / 2 - UkrainePaddle -> Height / 2;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::YesLabelClick(TObject *Sender)
{
        Obstacle1 -> Visible = true;
        Obstacle2 -> Visible = true;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::NoLabelClick(TObject *Sender)
{
        Obstacle1 -> Top = Pitch -> Top + Pitch -> Height - 40 - Obstacle1 -> Height;
        Obstacle2 -> Top = Pitch -> Top + 40;
        Obstacle1 -> Visible = false;
        Obstacle2 -> Visible = false;
}
//---------------------------------------------------------------------------



void __fastcall TForm1::ObstacleTimerTimer(TObject *Sender)
{
        Obstacle1 -> Top += y1;
        Obstacle2 -> Top += y2;

        //Obstacle1's top and bottom position
        if (Obstacle1 -> Top <= Pitch -> Top + 40 ||
            Obstacle1 -> Top + Obstacle1 -> Height >= Pitch -> Top + Pitch -> Height - 40)
        {
                y1 = -y1;
        }

        //Obstacle2's top and bottom position
        if (Obstacle2 -> Top <= Pitch -> Top + 40 ||
            Obstacle2 -> Top + Obstacle2 -> Height >= Pitch -> Top + Pitch -> Height - 40)
        {
                y2 = -y2;
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::IsBumpedOffTimerTimer(TObject *Sender)
{
        if (isBumpedOff == true)
        {
                isBumpedOff = false;
                IsBumpedOffTimer -> Enabled = false;
        }
}
//---------------------------------------------------------------------------

