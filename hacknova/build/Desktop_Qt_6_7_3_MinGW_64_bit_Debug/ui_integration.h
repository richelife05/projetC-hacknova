/********************************************************************************
** Form generated from reading UI file 'integration.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INTEGRATION_H
#define UI_INTEGRATION_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_integration
{
public:
    QWidget *centralWidget;
    QVBoxLayout *mainLayout;
    QStackedWidget *stackedWidget;
    QWidget *pageConnexion;
    QVBoxLayout *loginOuterLayout;
    QSpacerItem *loginSpacerTop;
    QHBoxLayout *loginCenterLayout;
    QSpacerItem *loginSpacerLeft;
    QFrame *frameLoginCard;
    QHBoxLayout *loginCardLayout;
    QFrame *frameLoginBrand;
    QVBoxLayout *loginBrandLayout;
    QLabel *labelLoginLogo;
    QLabel *labelLoginBrandTitle;
    QLabel *labelLoginBrandSub;
    QSpacerItem *loginBrandSpacer1;
    QFrame *frameLoginSeparator;
    QLabel *labelLoginBrandSlogan;
    QSpacerItem *loginBrandSpacer2;
    QLabel *labelLoginBrandVersion;
    QLabel *labelLoginBrandTeam;
    QVBoxLayout *loginFormLayout;
    QLabel *labelLoginTitle;
    QLabel *labelLoginSub;
    QSpacerItem *loginFormSpacer1;
    QLabel *labelLoginField;
    QLineEdit *lineEditIdentifiant;
    QLabel *labelLoginField2;
    QLineEdit *lineEditMotDePasse;
    QCheckBox *checkBoxSouvenir;
    QPushButton *pushButtonConnexion;
    QFrame *frameLoginSeparator2;
    QPushButton *pushButtonCGU;
    QPushButton *pushButtonPolitique;
    QPushButton *pushButtonAPropos;
    QSpacerItem *loginFormSpacer2;
    QLabel *labelLoginFooter;
    QSpacerItem *loginSpacerRight;
    QSpacerItem *loginSpacerBottom;
    QWidget *pageDashboard;
    QVBoxLayout *dashboardOuterLayout;
    QScrollArea *scrollDashboard;
    QWidget *scrollDashboardContent;
    QVBoxLayout *dashboardContentLayout;
    QFrame *frameNavbar;
    QHBoxLayout *navbarLayout;
    QLabel *labelNavLogo;
    QVBoxLayout *brandLayout;
    QLabel *labelNavBrand;
    QLabel *labelNavSub;
    QFrame *frameNavSeparator;
    QPushButton *navDashboardDashboard;
    QPushButton *navEmployesDashboard;
    QPushButton *navSallesDashboard;
    QPushButton *navEvaluateursDashboard;
    QPushButton *navParticipantsDashboard;
    QPushButton *navSponsorsDashboard;
    QPushButton *navProjetsDashboard;
    QSpacerItem *navbarSpacer;
    QPushButton *navDeconnexionDashboard;
    QFrame *frameTopbar;
    QHBoxLayout *topbarLayout;
    QVBoxLayout *topbarTitleLayout;
    QLabel *labelTopbarTitle;
    QLabel *labelTopbarSub;
    QSpacerItem *topbarSpacer;
    QPushButton *navNotifDashboard;
    QPushButton *navProfileDashboard;
    QVBoxLayout *topbarUserLayout;
    QLabel *labelTopbarUserName;
    QLabel *labelTopbarUserRole;
    QLabel *labelTopbarAvatar;
    QHBoxLayout *kpiLayout;
    QFrame *cardStat;
    QVBoxLayout *cardStatLayout;
    QLabel *cardStatTitle;
    QLabel *cardStatValue;
    QLabel *cardStatSub;
    QFrame *cardStat2;
    QVBoxLayout *cardStat2Layout;
    QLabel *cardStatTitle2;
    QLabel *cardStatValue2;
    QLabel *cardStatSub2;
    QFrame *cardStat3;
    QVBoxLayout *cardStat3Layout;
    QLabel *cardStatTitle3;
    QLabel *cardStatValue3;
    QLabel *cardStatSub3;
    QFrame *cardStat4;
    QVBoxLayout *cardStat4Layout;
    QLabel *cardStatTitle4;
    QLabel *cardStatValue4;
    QLabel *cardStatSub4;
    QHBoxLayout *chartsLayout;
    QFrame *cardDonut;
    QVBoxLayout *donutLayout;
    QLabel *labelDonutTitle;
    QLabel *labelDonutSub;
    QFrame *chartDonut;
    QVBoxLayout *donutCenterLayout;
    QFrame *chartDonutHole;
    QVBoxLayout *donutHoleLayout;
    QLabel *chartDonutCenterValue;
    QLabel *chartDonutCenterLabel;
    QSpacerItem *donutSpacer;
    QLabel *labelDonutFooter;
    QFrame *cardBarsH;
    QVBoxLayout *barsHLayout;
    QLabel *labelBarsHTitle;
    QLabel *labelBarsHSub;
    QHBoxLayout *bar1HeaderLayout;
    QLabel *barLabel1;
    QSpacerItem *bar1Spacer;
    QLabel *barValue1;
    QFrame *barHTrack1;
    QHBoxLayout *barHFill1Layout;
    QFrame *barHFill1;
    QSpacerItem *barHFillSpacer1;
    QHBoxLayout *bar2HeaderLayout;
    QLabel *barLabel2;
    QSpacerItem *bar2Spacer;
    QLabel *barValue2;
    QFrame *barHTrack2;
    QHBoxLayout *barHFill2Layout;
    QFrame *barHFill2;
    QSpacerItem *barHFillSpacer2;
    QHBoxLayout *bar3HeaderLayout;
    QLabel *barLabel3;
    QSpacerItem *bar3Spacer;
    QLabel *barValue3;
    QFrame *barHTrack3;
    QHBoxLayout *barHFill3Layout;
    QFrame *barHFill3;
    QSpacerItem *barHFillSpacer3;
    QHBoxLayout *bar4HeaderLayout;
    QLabel *barLabel4;
    QSpacerItem *bar4Spacer;
    QLabel *barValue4;
    QFrame *barHTrack4;
    QHBoxLayout *barHFill4Layout;
    QFrame *barHFill4;
    QSpacerItem *barHFillSpacer4;
    QSpacerItem *barsHSpacer;
    QLabel *labelProgressTitle;
    QProgressBar *progressBarHackathon;
    QLabel *labelProgressNote;
    QFrame *cardBarsV;
    QVBoxLayout *barsVLayout;
    QLabel *labelBarsVTitle;
    QLabel *labelBarsVSub;
    QHBoxLayout *barsVContainerLayout;
    QVBoxLayout *vBar1Layout;
    QLabel *barVValue1;
    QFrame *barVBar1;
    QLabel *barVLabel1;
    QVBoxLayout *vBar2Layout;
    QLabel *barVValue2;
    QFrame *barVBar2;
    QLabel *barVLabel2;
    QVBoxLayout *vBar3Layout;
    QLabel *barVValue3;
    QFrame *barVBar3;
    QLabel *barVLabel3;
    QVBoxLayout *vBar4Layout;
    QLabel *barVValue4;
    QFrame *barVBar4;
    QLabel *barVLabel4;
    QVBoxLayout *vBar5Layout;
    QLabel *barVValue5;
    QFrame *barVBar5;
    QLabel *barVLabel5;
    QVBoxLayout *vBar6Layout;
    QLabel *barVValue6;
    QFrame *barVBar6;
    QLabel *barVLabel6;
    QSpacerItem *barsVSpacer;
    QHBoxLayout *barsVFooterLayout;
    QLabel *labelBarsVFooterLeft;
    QSpacerItem *barsVFooterSpacer;
    QLabel *labelBarsVFooterRight;
    QFrame *cardChatbot;
    QVBoxLayout *chatbotLayout;
    QHBoxLayout *chatHeaderLayout;
    QLabel *chatTitle;
    QSpacerItem *chatHeaderSpacer;
    QLabel *chatStatusOnline;
    QLabel *chatSub;
    QHBoxLayout *chatContentLayout;
    QTextBrowser *chatDisplay;
    QVBoxLayout *chatQuickLayout;
    QLabel *chatQuickTitle;
    QPushButton *chatQuick1;
    QPushButton *chatQuick2;
    QPushButton *chatQuick3;
    QPushButton *chatQuick4;
    QSpacerItem *chatQuickSpacer;
    QHBoxLayout *chatInputLayout;
    QLineEdit *chatInput;
    QPushButton *chatSendBtn;
    QWidget *pageEmployes;
    QVBoxLayout *employesOuterLayout;
    QScrollArea *scrollEmployes;
    QWidget *scrollEmployesContent;
    QVBoxLayout *employesContentLayout;
    QFrame *frameNavbarEmployes;
    QHBoxLayout *navbarEmployesLayout;
    QLabel *labelNavLogoEmp;
    QVBoxLayout *brandEmpLayout;
    QLabel *labelNavBrandEmp;
    QLabel *labelNavSubEmp;
    QFrame *frameNavSepEmp;
    QPushButton *navDashboardEmployes;
    QPushButton *navEmployesEmployes;
    QPushButton *navSallesEmployes;
    QPushButton *navEvaluateursEmployes;
    QPushButton *navParticipantsEmployes;
    QPushButton *navSponsorsEmployes;
    QPushButton *navProjetsEmployes;
    QSpacerItem *navbarEmpSpacer;
    QPushButton *navDeconnexionEmployes;
    QFrame *frameTopbarEmployes;
    QVBoxLayout *topbarEmpLayout;
    QLabel *topbarTitleEmp;
    QLabel *topbarSubEmp;
    QHBoxLayout *statsEmpLayout;
    QFrame *cardEmpStat1;
    QVBoxLayout *cardEmpStat1Layout;
    QLabel *cardEmpTitle1;
    QLabel *cardEmpValue1;
    QLabel *cardEmpSub1;
    QFrame *cardEmpStat2;
    QVBoxLayout *cardEmpStat2Layout;
    QLabel *cardEmpTitle2;
    QLabel *cardEmpValue2;
    QLabel *cardEmpSub2;
    QFrame *cardEmpStat3;
    QVBoxLayout *cardEmpStat3Layout;
    QLabel *cardEmpTitle3;
    QLabel *cardEmpValue3;
    QLabel *cardEmpSub3;
    QFrame *cardEmpStat4;
    QVBoxLayout *cardEmpStat4Layout;
    QLabel *cardEmpTitle4;
    QLabel *cardEmpValue4;
    QLabel *cardEmpSub4;
    QFrame *cardFormEmployes;
    QVBoxLayout *formEmpLayout;
    QLabel *formTitleEmp;
    QGridLayout *formEmpGrid;
    QLabel *lblEmpID;
    QLabel *lblEmpNom;
    QLabel *lblEmpPrenom;
    QLabel *lblEmpMdp;
    QLabel *lblEmpRole;
    QLabel *lblEmpStatut;
    QLineEdit *lineEditEmpID;
    QLineEdit *lineEditEmpNom;
    QLineEdit *lineEditEmpPrenom;
    QLineEdit *lineEditEmpMdp;
    QComboBox *comboBoxEmpRole;
    QComboBox *comboBoxEmpStatut;
    QHBoxLayout *formEmpButtonsLayout;
    QPushButton *btnEmpAjouter;
    QPushButton *btnEmpModifier;
    QPushButton *btnEmpSupprimer;
    QPushButton *btnEmpConsulter;
    QSpacerItem *formEmpBtnSpacer;
    QHBoxLayout *searchEmpLayout;
    QLineEdit *lineEditRechercheEmployes;
    QPushButton *btnEmpRechercher;
    QPushButton *btnEmpTrier;
    QSpacerItem *searchEmpSpacer;
    QFrame *cardTableEmployes;
    QVBoxLayout *tableEmpLayout;
    QLabel *tableTitleEmp;
    QTableWidget *tableWidgetEmployes;
    QWidget *pageSalles;
    QVBoxLayout *sallesOuterLayout;
    QScrollArea *scrollSalles;
    QWidget *scrollSallesContent;
    QVBoxLayout *sallesContentLayout;
    QFrame *frameNavbarSalles;
    QHBoxLayout *navbarSallesLayout;
    QLabel *labelNavLogoSalles;
    QVBoxLayout *brandSallesLayout;
    QLabel *labelNavBrandSalles;
    QLabel *labelNavSubSalles;
    QFrame *frameNavSepSalles;
    QPushButton *navDashboardSalles;
    QPushButton *navEmployesSalles;
    QPushButton *navSallesSalles;
    QPushButton *navEvaluateursSalles;
    QPushButton *navParticipantsSalles;
    QPushButton *navSponsorsSalles;
    QPushButton *navProjetsSalles;
    QSpacerItem *navbarSallesSpacer;
    QPushButton *navDeconnexionSalles;
    QFrame *frameTopbarSalles;
    QVBoxLayout *topbarSallesLayout;
    QLabel *topbarTitleSalles;
    QLabel *topbarSubSalles;
    QHBoxLayout *statsSallesLayout;
    QFrame *cardSalleStat1;
    QVBoxLayout *cardSalleStat1Layout;
    QLabel *cardSalleTitle1;
    QLabel *cardSalleValue1;
    QLabel *cardSalleSub1;
    QFrame *cardSalleStat2;
    QVBoxLayout *cardSalleStat2Layout;
    QLabel *cardSalleTitle2;
    QLabel *cardSalleValue2;
    QLabel *cardSalleSub2;
    QFrame *cardSalleStat3;
    QVBoxLayout *cardSalleStat3Layout;
    QLabel *cardSalleTitle3;
    QLabel *cardSalleValue3;
    QLabel *cardSalleSub3;
    QFrame *cardSalleStat4;
    QVBoxLayout *cardSalleStat4Layout;
    QLabel *cardSalleTitle4;
    QLabel *cardSalleValue4;
    QLabel *cardSalleSub4;
    QFrame *cardFormSalles;
    QVBoxLayout *formSallesLayout;
    QLabel *formTitleSalles;
    QGridLayout *formSallesGrid;
    QLabel *lblSalleID;
    QLabel *lblSalleNom;
    QLabel *lblSalleCap;
    QLabel *lblSalleType;
    QLabel *lblSalleDispo;
    QLineEdit *lineEditSalleID;
    QLineEdit *lineEditSalleNom;
    QSpinBox *spinBoxSalleCapacite;
    QComboBox *comboBoxSalleType;
    QComboBox *comboBoxSalleDispo;
    QHBoxLayout *formSallesButtonsLayout;
    QPushButton *btnSalleAjouter;
    QPushButton *btnSalleModifier;
    QPushButton *btnSalleSupprimer;
    QPushButton *btnSalleConsulter;
    QSpacerItem *formSallesBtnSpacer;
    QHBoxLayout *searchSallesLayout;
    QLineEdit *lineEditRechercheSalle;
    QPushButton *btnSalleRechercher;
    QPushButton *btnSalleTrier;
    QSpacerItem *searchSallesSpacer;
    QFrame *cardTableSalles;
    QVBoxLayout *tableSallesLayout;
    QLabel *tableTitleSalles;
    QTableWidget *tableWidgetSalles;
    QWidget *pageEvaluateurs;
    QVBoxLayout *evaluateursOuterLayout;
    QScrollArea *scrollEvaluateurs;
    QWidget *scrollEvaluateursContent;
    QVBoxLayout *evaluateursContentLayout;
    QFrame *frameNavbarEvaluateurs;
    QHBoxLayout *navbarEvalLayout;
    QLabel *sbLogoEval;
    QVBoxLayout *brandEvalLayout;
    QLabel *sbBrandEval;
    QLabel *sbSubEval;
    QFrame *sbSepEval;
    QPushButton *navDashboardEvaluateurs;
    QPushButton *navEmployesEvaluateurs;
    QPushButton *navSallesEvaluateurs;
    QPushButton *navEvaluateursEvaluateurs;
    QPushButton *navParticipantsEvaluateurs;
    QPushButton *navSponsorsEvaluateurs;
    QPushButton *navProjetsEvaluateurs;
    QSpacerItem *navbarEvalSpacer;
    QPushButton *navDeconnexionEvaluateurs;
    QFrame *frameTopbarEvaluateurs;
    QVBoxLayout *topbarEvalLayout;
    QLabel *topbarTitleEval;
    QLabel *topbarSubEval;
    QHBoxLayout *statsEvalLayout;
    QFrame *cardEvalStat1;
    QVBoxLayout *cardEvalStat1Layout;
    QLabel *cardEvalTitle1;
    QLabel *cardEvalValue1;
    QLabel *cardEvalSub1;
    QFrame *cardEvalStat2;
    QVBoxLayout *cardEvalStat2Layout;
    QLabel *cardEvalTitle2;
    QLabel *cardEvalValue2;
    QLabel *cardEvalSub2;
    QFrame *cardEvalStat3;
    QVBoxLayout *cardEvalStat3Layout;
    QLabel *cardEvalTitle3;
    QLabel *cardEvalValue3;
    QLabel *cardEvalSub3;
    QFrame *cardFormEvaluateurs;
    QVBoxLayout *formEvalLayout;
    QLabel *formTitleEval;
    QGridLayout *formEvalGrid;
    QLabel *lblEvalID;
    QLabel *lblEvalNom;
    QLabel *lblEvalPrenom;
    QLabel *lblEvalEmail;
    QLabel *lblEvalStatut;
    QLineEdit *lineEditEvalID;
    QLineEdit *lineEditEvalNom;
    QLineEdit *lineEditEvalPrenom;
    QLineEdit *lineEditEvalEmail;
    QComboBox *comboBoxEvalStatut;
    QHBoxLayout *formEvalButtonsLayout;
    QPushButton *btnEvalAjouter;
    QPushButton *btnEvalModifier;
    QPushButton *btnEvalSupprimer;
    QPushButton *btnEvalConsulter;
    QSpacerItem *formEvalBtnSpacer;
    QHBoxLayout *searchEvalLayout;
    QLineEdit *lineEditRechercheEval;
    QPushButton *btnEvalRechercher;
    QPushButton *btnEvalTrier;
    QSpacerItem *searchEvalSpacer;
    QFrame *cardTableEvaluateurs;
    QVBoxLayout *tableEvalLayout;
    QLabel *tableTitleEval;
    QTableWidget *tableWidgetEvaluateurs;
    QWidget *pageParticipants;
    QVBoxLayout *participantsOuterLayout;
    QScrollArea *scrollParticipants;
    QWidget *scrollParticipantsContent;
    QVBoxLayout *participantsContentLayout;
    QFrame *frameNavbarParticipants;
    QHBoxLayout *navbarPartLayout;
    QLabel *sbLogoPart;
    QVBoxLayout *brandPartLayout;
    QLabel *sbBrandPart;
    QLabel *sbSubPart;
    QFrame *sbSepPart;
    QPushButton *navDashboardParticipants;
    QPushButton *navEmployesParticipants;
    QPushButton *navSallesParticipants;
    QPushButton *navEvaluateursParticipants;
    QPushButton *navParticipantsParticipants;
    QPushButton *navSponsorsParticipants;
    QPushButton *navProjetsParticipants;
    QSpacerItem *navbarPartSpacer;
    QPushButton *navDeconnexionParticipants;
    QFrame *frameTopbarParticipants;
    QVBoxLayout *topbarPartLayout;
    QLabel *topbarTitlePart;
    QLabel *topbarSubPart;
    QHBoxLayout *statsPartLayout;
    QFrame *cardPartStat1;
    QVBoxLayout *cardPartStat1Layout;
    QLabel *cardPartTitle1;
    QLabel *cardPartValue1;
    QLabel *cardPartSub1;
    QFrame *cardPartStat2;
    QVBoxLayout *cardPartStat2Layout;
    QLabel *cardPartTitle2;
    QLabel *cardPartValue2;
    QLabel *cardPartSub2;
    QFrame *cardPartStat3;
    QVBoxLayout *cardPartStat3Layout;
    QLabel *cardPartTitle3;
    QLabel *cardPartValue3;
    QLabel *cardPartSub3;
    QFrame *cardFormParticipants;
    QVBoxLayout *formPartLayout;
    QLabel *formTitlePart;
    QGridLayout *formPartGrid;
    QLabel *lblPartID;
    QLabel *lblPartNom;
    QLabel *lblPartPrenom;
    QLabel *lblPartEmail;
    QLabel *lblPartTel;
    QLabel *lblPartEquipe;
    QLineEdit *lineEditPartID;
    QLineEdit *lineEditPartNom;
    QLineEdit *lineEditPartPrenom;
    QLineEdit *lineEditPartEmail;
    QLineEdit *lineEditPartTel;
    QLineEdit *lineEditPartEquipe;
    QHBoxLayout *formPartButtonsLayout;
    QPushButton *btnPartAjouter;
    QPushButton *btnPartModifier;
    QPushButton *btnPartSupprimer;
    QPushButton *btnPartConsulter;
    QSpacerItem *formPartBtnSpacer;
    QHBoxLayout *searchPartLayout;
    QLineEdit *lineEditRecherchePart;
    QPushButton *btnPartRechercher;
    QPushButton *btnPartTrier;
    QSpacerItem *searchPartSpacer;
    QFrame *cardTableParticipants;
    QVBoxLayout *tablePartLayout;
    QLabel *tableTitlePart;
    QTableWidget *tableWidgetParticipants;
    QWidget *pageSponsors;
    QVBoxLayout *sponsorsOuterLayout;
    QScrollArea *scrollSponsors;
    QWidget *scrollSponsorsContent;
    QVBoxLayout *sponsorsContentLayout;
    QFrame *frameNavbarSponsors;
    QHBoxLayout *navbarSponLayout;
    QLabel *sbLogoSpon;
    QVBoxLayout *brandSponLayout;
    QLabel *sbBrandSpon;
    QLabel *sbSubSpon;
    QFrame *sbSepSpon;
    QPushButton *navDashboardSponsors;
    QPushButton *navEmployesSponsors;
    QPushButton *navSallesSponsors;
    QPushButton *navEvaluateursSponsors;
    QPushButton *navParticipantsSponsors;
    QPushButton *navSponsorsSponsors;
    QPushButton *navProjetsSponsors;
    QSpacerItem *navbarSponSpacer;
    QPushButton *navDeconnexionSponsors;
    QFrame *frameTopbarSponsors;
    QVBoxLayout *topbarSponLayout;
    QLabel *topbarTitleSpon;
    QLabel *topbarSubSpon;
    QHBoxLayout *statsSponLayout;
    QFrame *cardSponStat1;
    QVBoxLayout *cardSponStat1Layout;
    QLabel *cardSponTitle1;
    QLabel *cardSponValue1;
    QLabel *cardSponSub1;
    QFrame *cardSponStat2;
    QVBoxLayout *cardSponStat2Layout;
    QLabel *cardSponTitle2;
    QLabel *cardSponValue2;
    QLabel *cardSponSub2;
    QFrame *cardSponStat3;
    QVBoxLayout *cardSponStat3Layout;
    QLabel *cardSponTitle3;
    QLabel *cardSponValue3;
    QLabel *cardSponSub3;
    QFrame *cardFormSponsors;
    QVBoxLayout *formSponLayout;
    QLabel *formTitleSpon;
    QGridLayout *formSponGrid;
    QLabel *lblSponID;
    QLabel *lblSponEntreprise;
    QLabel *lblSponContact;
    QLabel *lblSponType;
    QLabel *lblSponStatut;
    QLineEdit *lineEditSponID;
    QLineEdit *lineEditSponEntreprise;
    QLineEdit *lineEditSponContact;
    QComboBox *comboBoxSponType;
    QComboBox *comboBoxSponStatut;
    QHBoxLayout *formSponButtonsLayout;
    QPushButton *btnSponAjouter;
    QPushButton *btnSponModifier;
    QPushButton *btnSponSupprimer;
    QPushButton *btnSponConsulter;
    QSpacerItem *formSponBtnSpacer;
    QHBoxLayout *searchSponLayout;
    QLineEdit *lineEditRechercheSpon;
    QPushButton *btnSponRechercher;
    QPushButton *btnSponTrier;
    QSpacerItem *searchSponSpacer;
    QFrame *cardTableSponsors;
    QVBoxLayout *tableSponLayout;
    QLabel *tableTitleSpon;
    QTableWidget *tableWidgetSponsors;
    QWidget *pageProjets;
    QVBoxLayout *projetsOuterLayout;
    QScrollArea *scrollProjets;
    QWidget *scrollProjetsContent;
    QVBoxLayout *projetsContentLayout;
    QFrame *frameNavbarProjets;
    QHBoxLayout *navbarProjLayout;
    QLabel *sbLogoProj;
    QVBoxLayout *brandProjLayout;
    QLabel *sbBrandProj;
    QLabel *sbSubProj;
    QFrame *sbSepProj;
    QPushButton *navDashboardProjets;
    QPushButton *navEmployesProjets;
    QPushButton *navSallesProjets;
    QPushButton *navEvaluateursProjets;
    QPushButton *navParticipantsProjets;
    QPushButton *navSponsorsProjets;
    QPushButton *navProjetsProjets;
    QSpacerItem *navbarProjSpacer;
    QPushButton *navDeconnexionProjets;
    QFrame *frameTopbarProjets;
    QVBoxLayout *topbarProjLayout;
    QLabel *topbarTitleProj;
    QLabel *topbarSubProj;
    QHBoxLayout *statsProjLayout;
    QFrame *cardProjStat1;
    QVBoxLayout *cardProjStat1Layout;
    QLabel *cardProjTitle1;
    QLabel *cardProjValue1;
    QLabel *cardProjSub1;
    QFrame *cardProjStat2;
    QVBoxLayout *cardProjStat2Layout;
    QLabel *cardProjTitle2;
    QLabel *cardProjValue2;
    QLabel *cardProjSub2;
    QFrame *cardProjStat3;
    QVBoxLayout *cardProjStat3Layout;
    QLabel *cardProjTitle3;
    QLabel *cardProjValue3;
    QLabel *cardProjSub3;
    QFrame *cardProjStat4;
    QVBoxLayout *cardProjStat4Layout;
    QLabel *cardProjTitle4;
    QLabel *cardProjValue4;
    QLabel *cardProjSub4;
    QFrame *cardFormProjets;
    QVBoxLayout *formProjLayout;
    QLabel *formTitleProj;
    QGridLayout *formProjGrid;
    QLabel *lblProjID;
    QLabel *lblProjNom;
    QLabel *lblProjCat;
    QLabel *lblProjStatut;
    QLabel *lblProjEquipe;
    QLineEdit *lineEditProjID;
    QLineEdit *lineEditProjNom;
    QComboBox *comboBoxProjCategorie;
    QComboBox *comboBoxProjStatut;
    QLineEdit *lineEditProjEquipe;
    QHBoxLayout *formProjButtonsLayout;
    QPushButton *btnProjAjouter;
    QPushButton *btnProjModifier;
    QPushButton *btnProjSupprimer;
    QPushButton *btnProjConsulter;
    QSpacerItem *formProjBtnSpacer;
    QHBoxLayout *searchProjLayout;
    QLineEdit *lineEditRechercheProj;
    QPushButton *btnProjRechercher;
    QPushButton *btnProjTrier;
    QSpacerItem *searchProjSpacer;
    QFrame *cardTableProjets;
    QVBoxLayout *tableProjLayout;
    QLabel *tableTitleProj;
    QTableWidget *tableWidgetProjets;

    void setupUi(QMainWindow *integration)
    {
        if (integration->objectName().isEmpty())
            integration->setObjectName("integration");
        integration->resize(1440, 900);
        integration->setMinimumSize(QSize(1280, 720));
        centralWidget = new QWidget(integration);
        centralWidget->setObjectName("centralWidget");
        mainLayout = new QVBoxLayout(centralWidget);
        mainLayout->setSpacing(0);
        mainLayout->setObjectName("mainLayout");
        mainLayout->setContentsMargins(0, 0, 0, 0);
        stackedWidget = new QStackedWidget(centralWidget);
        stackedWidget->setObjectName("stackedWidget");
        pageConnexion = new QWidget();
        pageConnexion->setObjectName("pageConnexion");
        loginOuterLayout = new QVBoxLayout(pageConnexion);
        loginOuterLayout->setSpacing(0);
        loginOuterLayout->setObjectName("loginOuterLayout");
        loginOuterLayout->setContentsMargins(0, 0, 0, 0);
        loginSpacerTop = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        loginOuterLayout->addItem(loginSpacerTop);

        loginCenterLayout = new QHBoxLayout();
        loginCenterLayout->setSpacing(0);
        loginCenterLayout->setObjectName("loginCenterLayout");
        loginSpacerLeft = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        loginCenterLayout->addItem(loginSpacerLeft);

        frameLoginCard = new QFrame(pageConnexion);
        frameLoginCard->setObjectName("frameLoginCard");
        frameLoginCard->setMinimumSize(QSize(900, 620));
        frameLoginCard->setMaximumSize(QSize(1100, 720));
        loginCardLayout = new QHBoxLayout(frameLoginCard);
        loginCardLayout->setSpacing(0);
        loginCardLayout->setObjectName("loginCardLayout");
        loginCardLayout->setContentsMargins(0, 0, 0, 0);
        frameLoginBrand = new QFrame(frameLoginCard);
        frameLoginBrand->setObjectName("frameLoginBrand");
        frameLoginBrand->setMinimumSize(QSize(420, 0));
        frameLoginBrand->setMaximumSize(QSize(420, 16777215));
        loginBrandLayout = new QVBoxLayout(frameLoginBrand);
        loginBrandLayout->setSpacing(18);
        loginBrandLayout->setObjectName("loginBrandLayout");
        loginBrandLayout->setContentsMargins(40, 60, 40, 60);
        labelLoginLogo = new QLabel(frameLoginBrand);
        labelLoginLogo->setObjectName("labelLoginLogo");
        labelLoginLogo->setMinimumSize(QSize(100, 100));
        labelLoginLogo->setMaximumSize(QSize(100, 100));
        labelLoginLogo->setAlignment(Qt::AlignmentFlag::AlignCenter);

        loginBrandLayout->addWidget(labelLoginLogo);

        labelLoginBrandTitle = new QLabel(frameLoginBrand);
        labelLoginBrandTitle->setObjectName("labelLoginBrandTitle");
        labelLoginBrandTitle->setAlignment(Qt::AlignmentFlag::AlignCenter);

        loginBrandLayout->addWidget(labelLoginBrandTitle);

        labelLoginBrandSub = new QLabel(frameLoginBrand);
        labelLoginBrandSub->setObjectName("labelLoginBrandSub");
        labelLoginBrandSub->setAlignment(Qt::AlignmentFlag::AlignCenter);

        loginBrandLayout->addWidget(labelLoginBrandSub);

        loginBrandSpacer1 = new QSpacerItem(20, 20, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        loginBrandLayout->addItem(loginBrandSpacer1);

        frameLoginSeparator = new QFrame(frameLoginBrand);
        frameLoginSeparator->setObjectName("frameLoginSeparator");
        frameLoginSeparator->setMinimumSize(QSize(0, 1));
        frameLoginSeparator->setMaximumSize(QSize(16777215, 1));

        loginBrandLayout->addWidget(frameLoginSeparator);

        labelLoginBrandSlogan = new QLabel(frameLoginBrand);
        labelLoginBrandSlogan->setObjectName("labelLoginBrandSlogan");
        labelLoginBrandSlogan->setAlignment(Qt::AlignmentFlag::AlignCenter);
        labelLoginBrandSlogan->setWordWrap(true);

        loginBrandLayout->addWidget(labelLoginBrandSlogan);

        loginBrandSpacer2 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        loginBrandLayout->addItem(loginBrandSpacer2);

        labelLoginBrandVersion = new QLabel(frameLoginBrand);
        labelLoginBrandVersion->setObjectName("labelLoginBrandVersion");
        labelLoginBrandVersion->setAlignment(Qt::AlignmentFlag::AlignCenter);

        loginBrandLayout->addWidget(labelLoginBrandVersion);

        labelLoginBrandTeam = new QLabel(frameLoginBrand);
        labelLoginBrandTeam->setObjectName("labelLoginBrandTeam");
        labelLoginBrandTeam->setAlignment(Qt::AlignmentFlag::AlignCenter);

        loginBrandLayout->addWidget(labelLoginBrandTeam);


        loginCardLayout->addWidget(frameLoginBrand);

        loginFormLayout = new QVBoxLayout();
        loginFormLayout->setSpacing(14);
        loginFormLayout->setObjectName("loginFormLayout");
        loginFormLayout->setContentsMargins(60, 60, 60, 60);
        labelLoginTitle = new QLabel(frameLoginCard);
        labelLoginTitle->setObjectName("labelLoginTitle");

        loginFormLayout->addWidget(labelLoginTitle);

        labelLoginSub = new QLabel(frameLoginCard);
        labelLoginSub->setObjectName("labelLoginSub");

        loginFormLayout->addWidget(labelLoginSub);

        loginFormSpacer1 = new QSpacerItem(20, 10, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        loginFormLayout->addItem(loginFormSpacer1);

        labelLoginField = new QLabel(frameLoginCard);
        labelLoginField->setObjectName("labelLoginField");

        loginFormLayout->addWidget(labelLoginField);

        lineEditIdentifiant = new QLineEdit(frameLoginCard);
        lineEditIdentifiant->setObjectName("lineEditIdentifiant");
        lineEditIdentifiant->setMinimumSize(QSize(0, 48));

        loginFormLayout->addWidget(lineEditIdentifiant);

        labelLoginField2 = new QLabel(frameLoginCard);
        labelLoginField2->setObjectName("labelLoginField2");

        loginFormLayout->addWidget(labelLoginField2);

        lineEditMotDePasse = new QLineEdit(frameLoginCard);
        lineEditMotDePasse->setObjectName("lineEditMotDePasse");
        lineEditMotDePasse->setMinimumSize(QSize(0, 48));
        lineEditMotDePasse->setEchoMode(QLineEdit::EchoMode::Password);

        loginFormLayout->addWidget(lineEditMotDePasse);

        checkBoxSouvenir = new QCheckBox(frameLoginCard);
        checkBoxSouvenir->setObjectName("checkBoxSouvenir");

        loginFormLayout->addWidget(checkBoxSouvenir);

        pushButtonConnexion = new QPushButton(frameLoginCard);
        pushButtonConnexion->setObjectName("pushButtonConnexion");
        pushButtonConnexion->setMinimumSize(QSize(0, 54));
        pushButtonConnexion->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        loginFormLayout->addWidget(pushButtonConnexion);

        frameLoginSeparator2 = new QFrame(frameLoginCard);
        frameLoginSeparator2->setObjectName("frameLoginSeparator2");
        frameLoginSeparator2->setMinimumSize(QSize(0, 1));
        frameLoginSeparator2->setMaximumSize(QSize(16777215, 1));

        loginFormLayout->addWidget(frameLoginSeparator2);

        pushButtonCGU = new QPushButton(frameLoginCard);
        pushButtonCGU->setObjectName("pushButtonCGU");
        pushButtonCGU->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        loginFormLayout->addWidget(pushButtonCGU);

        pushButtonPolitique = new QPushButton(frameLoginCard);
        pushButtonPolitique->setObjectName("pushButtonPolitique");
        pushButtonPolitique->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        loginFormLayout->addWidget(pushButtonPolitique);

        pushButtonAPropos = new QPushButton(frameLoginCard);
        pushButtonAPropos->setObjectName("pushButtonAPropos");
        pushButtonAPropos->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        loginFormLayout->addWidget(pushButtonAPropos);

        loginFormSpacer2 = new QSpacerItem(20, 10, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        loginFormLayout->addItem(loginFormSpacer2);

        labelLoginFooter = new QLabel(frameLoginCard);
        labelLoginFooter->setObjectName("labelLoginFooter");
        labelLoginFooter->setAlignment(Qt::AlignmentFlag::AlignCenter);

        loginFormLayout->addWidget(labelLoginFooter);


        loginCardLayout->addLayout(loginFormLayout);


        loginCenterLayout->addWidget(frameLoginCard);

        loginSpacerRight = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        loginCenterLayout->addItem(loginSpacerRight);


        loginOuterLayout->addLayout(loginCenterLayout);

        loginSpacerBottom = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        loginOuterLayout->addItem(loginSpacerBottom);

        stackedWidget->addWidget(pageConnexion);
        pageDashboard = new QWidget();
        pageDashboard->setObjectName("pageDashboard");
        dashboardOuterLayout = new QVBoxLayout(pageDashboard);
        dashboardOuterLayout->setSpacing(0);
        dashboardOuterLayout->setObjectName("dashboardOuterLayout");
        dashboardOuterLayout->setContentsMargins(0, 0, 0, 0);
        scrollDashboard = new QScrollArea(pageDashboard);
        scrollDashboard->setObjectName("scrollDashboard");
        scrollDashboard->setFrameShape(QFrame::Shape::NoFrame);
        scrollDashboard->setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAsNeeded);
        scrollDashboard->setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAsNeeded);
        scrollDashboard->setWidgetResizable(true);
        scrollDashboardContent = new QWidget();
        scrollDashboardContent->setObjectName("scrollDashboardContent");
        scrollDashboardContent->setGeometry(QRect(0, 0, 1045, 1253));
        dashboardContentLayout = new QVBoxLayout(scrollDashboardContent);
        dashboardContentLayout->setSpacing(0);
        dashboardContentLayout->setObjectName("dashboardContentLayout");
        dashboardContentLayout->setContentsMargins(0, 0, 0, 0);
        frameNavbar = new QFrame(scrollDashboardContent);
        frameNavbar->setObjectName("frameNavbar");
        frameNavbar->setMinimumSize(QSize(0, 76));
        frameNavbar->setMaximumSize(QSize(16777215, 76));
        navbarLayout = new QHBoxLayout(frameNavbar);
        navbarLayout->setSpacing(0);
        navbarLayout->setObjectName("navbarLayout");
        navbarLayout->setContentsMargins(24, 0, 24, 0);
        labelNavLogo = new QLabel(frameNavbar);
        labelNavLogo->setObjectName("labelNavLogo");
        labelNavLogo->setMinimumSize(QSize(44, 44));
        labelNavLogo->setMaximumSize(QSize(44, 44));
        labelNavLogo->setAlignment(Qt::AlignmentFlag::AlignCenter);

        navbarLayout->addWidget(labelNavLogo);

        brandLayout = new QVBoxLayout();
        brandLayout->setSpacing(0);
        brandLayout->setObjectName("brandLayout");
        brandLayout->setContentsMargins(12, -1, -1, -1);
        labelNavBrand = new QLabel(frameNavbar);
        labelNavBrand->setObjectName("labelNavBrand");

        brandLayout->addWidget(labelNavBrand);

        labelNavSub = new QLabel(frameNavbar);
        labelNavSub->setObjectName("labelNavSub");

        brandLayout->addWidget(labelNavSub);


        navbarLayout->addLayout(brandLayout);

        frameNavSeparator = new QFrame(frameNavbar);
        frameNavSeparator->setObjectName("frameNavSeparator");
        frameNavSeparator->setMinimumSize(QSize(1, 40));
        frameNavSeparator->setMaximumSize(QSize(1, 40));

        navbarLayout->addWidget(frameNavSeparator);

        navDashboardDashboard = new QPushButton(frameNavbar);
        navDashboardDashboard->setObjectName("navDashboardDashboard");
        navDashboardDashboard->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        navbarLayout->addWidget(navDashboardDashboard);

        navEmployesDashboard = new QPushButton(frameNavbar);
        navEmployesDashboard->setObjectName("navEmployesDashboard");
        navEmployesDashboard->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        navbarLayout->addWidget(navEmployesDashboard);

        navSallesDashboard = new QPushButton(frameNavbar);
        navSallesDashboard->setObjectName("navSallesDashboard");
        navSallesDashboard->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        navbarLayout->addWidget(navSallesDashboard);

        navEvaluateursDashboard = new QPushButton(frameNavbar);
        navEvaluateursDashboard->setObjectName("navEvaluateursDashboard");
        navEvaluateursDashboard->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        navbarLayout->addWidget(navEvaluateursDashboard);

        navParticipantsDashboard = new QPushButton(frameNavbar);
        navParticipantsDashboard->setObjectName("navParticipantsDashboard");
        navParticipantsDashboard->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        navbarLayout->addWidget(navParticipantsDashboard);

        navSponsorsDashboard = new QPushButton(frameNavbar);
        navSponsorsDashboard->setObjectName("navSponsorsDashboard");
        navSponsorsDashboard->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        navbarLayout->addWidget(navSponsorsDashboard);

        navProjetsDashboard = new QPushButton(frameNavbar);
        navProjetsDashboard->setObjectName("navProjetsDashboard");
        navProjetsDashboard->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        navbarLayout->addWidget(navProjetsDashboard);

        navbarSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        navbarLayout->addItem(navbarSpacer);

        navDeconnexionDashboard = new QPushButton(frameNavbar);
        navDeconnexionDashboard->setObjectName("navDeconnexionDashboard");
        navDeconnexionDashboard->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        navbarLayout->addWidget(navDeconnexionDashboard);


        dashboardContentLayout->addWidget(frameNavbar);

        frameTopbar = new QFrame(scrollDashboardContent);
        frameTopbar->setObjectName("frameTopbar");
        frameTopbar->setMinimumSize(QSize(0, 76));
        frameTopbar->setMaximumSize(QSize(16777215, 76));
        topbarLayout = new QHBoxLayout(frameTopbar);
        topbarLayout->setSpacing(16);
        topbarLayout->setObjectName("topbarLayout");
        topbarLayout->setContentsMargins(32, 14, 32, 14);
        topbarTitleLayout = new QVBoxLayout();
        topbarTitleLayout->setSpacing(2);
        topbarTitleLayout->setObjectName("topbarTitleLayout");
        labelTopbarTitle = new QLabel(frameTopbar);
        labelTopbarTitle->setObjectName("labelTopbarTitle");

        topbarTitleLayout->addWidget(labelTopbarTitle);

        labelTopbarSub = new QLabel(frameTopbar);
        labelTopbarSub->setObjectName("labelTopbarSub");

        topbarTitleLayout->addWidget(labelTopbarSub);


        topbarLayout->addLayout(topbarTitleLayout);

        topbarSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        topbarLayout->addItem(topbarSpacer);

        navNotifDashboard = new QPushButton(frameTopbar);
        navNotifDashboard->setObjectName("navNotifDashboard");
        navNotifDashboard->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        topbarLayout->addWidget(navNotifDashboard);

        navProfileDashboard = new QPushButton(frameTopbar);
        navProfileDashboard->setObjectName("navProfileDashboard");
        navProfileDashboard->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        topbarLayout->addWidget(navProfileDashboard);

        topbarUserLayout = new QVBoxLayout();
        topbarUserLayout->setSpacing(0);
        topbarUserLayout->setObjectName("topbarUserLayout");
        labelTopbarUserName = new QLabel(frameTopbar);
        labelTopbarUserName->setObjectName("labelTopbarUserName");

        topbarUserLayout->addWidget(labelTopbarUserName);

        labelTopbarUserRole = new QLabel(frameTopbar);
        labelTopbarUserRole->setObjectName("labelTopbarUserRole");

        topbarUserLayout->addWidget(labelTopbarUserRole);


        topbarLayout->addLayout(topbarUserLayout);

        labelTopbarAvatar = new QLabel(frameTopbar);
        labelTopbarAvatar->setObjectName("labelTopbarAvatar");
        labelTopbarAvatar->setMinimumSize(QSize(40, 40));
        labelTopbarAvatar->setMaximumSize(QSize(40, 40));
        labelTopbarAvatar->setAlignment(Qt::AlignmentFlag::AlignCenter);

        topbarLayout->addWidget(labelTopbarAvatar);


        dashboardContentLayout->addWidget(frameTopbar);

        kpiLayout = new QHBoxLayout();
        kpiLayout->setSpacing(16);
        kpiLayout->setObjectName("kpiLayout");
        kpiLayout->setContentsMargins(32, 20, 32, 20);
        cardStat = new QFrame(scrollDashboardContent);
        cardStat->setObjectName("cardStat");
        cardStat->setMinimumSize(QSize(0, 120));
        cardStatLayout = new QVBoxLayout(cardStat);
        cardStatLayout->setSpacing(4);
        cardStatLayout->setObjectName("cardStatLayout");
        cardStatLayout->setContentsMargins(20, 18, 20, 18);
        cardStatTitle = new QLabel(cardStat);
        cardStatTitle->setObjectName("cardStatTitle");

        cardStatLayout->addWidget(cardStatTitle);

        cardStatValue = new QLabel(cardStat);
        cardStatValue->setObjectName("cardStatValue");

        cardStatLayout->addWidget(cardStatValue);

        cardStatSub = new QLabel(cardStat);
        cardStatSub->setObjectName("cardStatSub");

        cardStatLayout->addWidget(cardStatSub);


        kpiLayout->addWidget(cardStat);

        cardStat2 = new QFrame(scrollDashboardContent);
        cardStat2->setObjectName("cardStat2");
        cardStat2->setMinimumSize(QSize(0, 120));
        cardStat2Layout = new QVBoxLayout(cardStat2);
        cardStat2Layout->setSpacing(4);
        cardStat2Layout->setObjectName("cardStat2Layout");
        cardStat2Layout->setContentsMargins(20, 18, 20, 18);
        cardStatTitle2 = new QLabel(cardStat2);
        cardStatTitle2->setObjectName("cardStatTitle2");

        cardStat2Layout->addWidget(cardStatTitle2);

        cardStatValue2 = new QLabel(cardStat2);
        cardStatValue2->setObjectName("cardStatValue2");

        cardStat2Layout->addWidget(cardStatValue2);

        cardStatSub2 = new QLabel(cardStat2);
        cardStatSub2->setObjectName("cardStatSub2");

        cardStat2Layout->addWidget(cardStatSub2);


        kpiLayout->addWidget(cardStat2);

        cardStat3 = new QFrame(scrollDashboardContent);
        cardStat3->setObjectName("cardStat3");
        cardStat3->setMinimumSize(QSize(0, 120));
        cardStat3Layout = new QVBoxLayout(cardStat3);
        cardStat3Layout->setSpacing(4);
        cardStat3Layout->setObjectName("cardStat3Layout");
        cardStat3Layout->setContentsMargins(20, 18, 20, 18);
        cardStatTitle3 = new QLabel(cardStat3);
        cardStatTitle3->setObjectName("cardStatTitle3");

        cardStat3Layout->addWidget(cardStatTitle3);

        cardStatValue3 = new QLabel(cardStat3);
        cardStatValue3->setObjectName("cardStatValue3");

        cardStat3Layout->addWidget(cardStatValue3);

        cardStatSub3 = new QLabel(cardStat3);
        cardStatSub3->setObjectName("cardStatSub3");

        cardStat3Layout->addWidget(cardStatSub3);


        kpiLayout->addWidget(cardStat3);

        cardStat4 = new QFrame(scrollDashboardContent);
        cardStat4->setObjectName("cardStat4");
        cardStat4->setMinimumSize(QSize(0, 120));
        cardStat4Layout = new QVBoxLayout(cardStat4);
        cardStat4Layout->setSpacing(4);
        cardStat4Layout->setObjectName("cardStat4Layout");
        cardStat4Layout->setContentsMargins(20, 18, 20, 18);
        cardStatTitle4 = new QLabel(cardStat4);
        cardStatTitle4->setObjectName("cardStatTitle4");

        cardStat4Layout->addWidget(cardStatTitle4);

        cardStatValue4 = new QLabel(cardStat4);
        cardStatValue4->setObjectName("cardStatValue4");

        cardStat4Layout->addWidget(cardStatValue4);

        cardStatSub4 = new QLabel(cardStat4);
        cardStatSub4->setObjectName("cardStatSub4");

        cardStat4Layout->addWidget(cardStatSub4);


        kpiLayout->addWidget(cardStat4);


        dashboardContentLayout->addLayout(kpiLayout);

        chartsLayout = new QHBoxLayout();
        chartsLayout->setSpacing(16);
        chartsLayout->setObjectName("chartsLayout");
        chartsLayout->setContentsMargins(32, 0, 32, 20);
        cardDonut = new QFrame(scrollDashboardContent);
        cardDonut->setObjectName("cardDonut");
        cardDonut->setMinimumSize(QSize(0, 420));
        donutLayout = new QVBoxLayout(cardDonut);
        donutLayout->setSpacing(12);
        donutLayout->setObjectName("donutLayout");
        donutLayout->setContentsMargins(24, 20, 24, 20);
        labelDonutTitle = new QLabel(cardDonut);
        labelDonutTitle->setObjectName("labelDonutTitle");

        donutLayout->addWidget(labelDonutTitle);

        labelDonutSub = new QLabel(cardDonut);
        labelDonutSub->setObjectName("labelDonutSub");

        donutLayout->addWidget(labelDonutSub);

        chartDonut = new QFrame(cardDonut);
        chartDonut->setObjectName("chartDonut");
        chartDonut->setMinimumSize(QSize(140, 140));
        chartDonut->setMaximumSize(QSize(140, 140));
        donutCenterLayout = new QVBoxLayout(chartDonut);
        donutCenterLayout->setObjectName("donutCenterLayout");
        donutCenterLayout->setContentsMargins(28, 28, 28, 28);
        chartDonutHole = new QFrame(chartDonut);
        chartDonutHole->setObjectName("chartDonutHole");
        donutHoleLayout = new QVBoxLayout(chartDonutHole);
        donutHoleLayout->setSpacing(0);
        donutHoleLayout->setObjectName("donutHoleLayout");
        donutHoleLayout->setContentsMargins(0, 0, 0, 0);
        chartDonutCenterValue = new QLabel(chartDonutHole);
        chartDonutCenterValue->setObjectName("chartDonutCenterValue");
        chartDonutCenterValue->setAlignment(Qt::AlignmentFlag::AlignCenter);

        donutHoleLayout->addWidget(chartDonutCenterValue);

        chartDonutCenterLabel = new QLabel(chartDonutHole);
        chartDonutCenterLabel->setObjectName("chartDonutCenterLabel");
        chartDonutCenterLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        donutHoleLayout->addWidget(chartDonutCenterLabel);


        donutCenterLayout->addWidget(chartDonutHole);


        donutLayout->addWidget(chartDonut);

        donutSpacer = new QSpacerItem(20, 20, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        donutLayout->addItem(donutSpacer);

        labelDonutFooter = new QLabel(cardDonut);
        labelDonutFooter->setObjectName("labelDonutFooter");

        donutLayout->addWidget(labelDonutFooter);


        chartsLayout->addWidget(cardDonut);

        cardBarsH = new QFrame(scrollDashboardContent);
        cardBarsH->setObjectName("cardBarsH");
        cardBarsH->setMinimumSize(QSize(0, 420));
        barsHLayout = new QVBoxLayout(cardBarsH);
        barsHLayout->setSpacing(10);
        barsHLayout->setObjectName("barsHLayout");
        barsHLayout->setContentsMargins(24, 20, 24, 20);
        labelBarsHTitle = new QLabel(cardBarsH);
        labelBarsHTitle->setObjectName("labelBarsHTitle");

        barsHLayout->addWidget(labelBarsHTitle);

        labelBarsHSub = new QLabel(cardBarsH);
        labelBarsHSub->setObjectName("labelBarsHSub");

        barsHLayout->addWidget(labelBarsHSub);

        bar1HeaderLayout = new QHBoxLayout();
        bar1HeaderLayout->setObjectName("bar1HeaderLayout");
        barLabel1 = new QLabel(cardBarsH);
        barLabel1->setObjectName("barLabel1");

        bar1HeaderLayout->addWidget(barLabel1);

        bar1Spacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        bar1HeaderLayout->addItem(bar1Spacer);

        barValue1 = new QLabel(cardBarsH);
        barValue1->setObjectName("barValue1");

        bar1HeaderLayout->addWidget(barValue1);


        barsHLayout->addLayout(bar1HeaderLayout);

        barHTrack1 = new QFrame(cardBarsH);
        barHTrack1->setObjectName("barHTrack1");
        barHTrack1->setMinimumSize(QSize(0, 10));
        barHTrack1->setMaximumSize(QSize(16777215, 10));
        barHFill1Layout = new QHBoxLayout(barHTrack1);
        barHFill1Layout->setSpacing(0);
        barHFill1Layout->setObjectName("barHFill1Layout");
        barHFill1Layout->setContentsMargins(0, 0, 0, 0);
        barHFill1 = new QFrame(barHTrack1);
        barHFill1->setObjectName("barHFill1");
        barHFill1->setMinimumSize(QSize(0, 10));
        barHFill1->setMaximumSize(QSize(16777215, 10));

        barHFill1Layout->addWidget(barHFill1);

        barHFillSpacer1 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        barHFill1Layout->addItem(barHFillSpacer1);


        barsHLayout->addWidget(barHTrack1);

        bar2HeaderLayout = new QHBoxLayout();
        bar2HeaderLayout->setObjectName("bar2HeaderLayout");
        barLabel2 = new QLabel(cardBarsH);
        barLabel2->setObjectName("barLabel2");

        bar2HeaderLayout->addWidget(barLabel2);

        bar2Spacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        bar2HeaderLayout->addItem(bar2Spacer);

        barValue2 = new QLabel(cardBarsH);
        barValue2->setObjectName("barValue2");

        bar2HeaderLayout->addWidget(barValue2);


        barsHLayout->addLayout(bar2HeaderLayout);

        barHTrack2 = new QFrame(cardBarsH);
        barHTrack2->setObjectName("barHTrack2");
        barHTrack2->setMinimumSize(QSize(0, 10));
        barHTrack2->setMaximumSize(QSize(16777215, 10));
        barHFill2Layout = new QHBoxLayout(barHTrack2);
        barHFill2Layout->setSpacing(0);
        barHFill2Layout->setObjectName("barHFill2Layout");
        barHFill2Layout->setContentsMargins(0, 0, 0, 0);
        barHFill2 = new QFrame(barHTrack2);
        barHFill2->setObjectName("barHFill2");
        barHFill2->setMinimumSize(QSize(0, 10));
        barHFill2->setMaximumSize(QSize(16777215, 10));

        barHFill2Layout->addWidget(barHFill2);

        barHFillSpacer2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        barHFill2Layout->addItem(barHFillSpacer2);


        barsHLayout->addWidget(barHTrack2);

        bar3HeaderLayout = new QHBoxLayout();
        bar3HeaderLayout->setObjectName("bar3HeaderLayout");
        barLabel3 = new QLabel(cardBarsH);
        barLabel3->setObjectName("barLabel3");

        bar3HeaderLayout->addWidget(barLabel3);

        bar3Spacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        bar3HeaderLayout->addItem(bar3Spacer);

        barValue3 = new QLabel(cardBarsH);
        barValue3->setObjectName("barValue3");

        bar3HeaderLayout->addWidget(barValue3);


        barsHLayout->addLayout(bar3HeaderLayout);

        barHTrack3 = new QFrame(cardBarsH);
        barHTrack3->setObjectName("barHTrack3");
        barHTrack3->setMinimumSize(QSize(0, 10));
        barHTrack3->setMaximumSize(QSize(16777215, 10));
        barHFill3Layout = new QHBoxLayout(barHTrack3);
        barHFill3Layout->setSpacing(0);
        barHFill3Layout->setObjectName("barHFill3Layout");
        barHFill3Layout->setContentsMargins(0, 0, 0, 0);
        barHFill3 = new QFrame(barHTrack3);
        barHFill3->setObjectName("barHFill3");
        barHFill3->setMinimumSize(QSize(0, 10));
        barHFill3->setMaximumSize(QSize(16777215, 10));

        barHFill3Layout->addWidget(barHFill3);

        barHFillSpacer3 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        barHFill3Layout->addItem(barHFillSpacer3);


        barsHLayout->addWidget(barHTrack3);

        bar4HeaderLayout = new QHBoxLayout();
        bar4HeaderLayout->setObjectName("bar4HeaderLayout");
        barLabel4 = new QLabel(cardBarsH);
        barLabel4->setObjectName("barLabel4");

        bar4HeaderLayout->addWidget(barLabel4);

        bar4Spacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        bar4HeaderLayout->addItem(bar4Spacer);

        barValue4 = new QLabel(cardBarsH);
        barValue4->setObjectName("barValue4");

        bar4HeaderLayout->addWidget(barValue4);


        barsHLayout->addLayout(bar4HeaderLayout);

        barHTrack4 = new QFrame(cardBarsH);
        barHTrack4->setObjectName("barHTrack4");
        barHTrack4->setMinimumSize(QSize(0, 10));
        barHTrack4->setMaximumSize(QSize(16777215, 10));
        barHFill4Layout = new QHBoxLayout(barHTrack4);
        barHFill4Layout->setSpacing(0);
        barHFill4Layout->setObjectName("barHFill4Layout");
        barHFill4Layout->setContentsMargins(0, 0, 0, 0);
        barHFill4 = new QFrame(barHTrack4);
        barHFill4->setObjectName("barHFill4");
        barHFill4->setMinimumSize(QSize(0, 10));
        barHFill4->setMaximumSize(QSize(16777215, 10));

        barHFill4Layout->addWidget(barHFill4);

        barHFillSpacer4 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        barHFill4Layout->addItem(barHFillSpacer4);


        barsHLayout->addWidget(barHTrack4);

        barsHSpacer = new QSpacerItem(20, 20, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        barsHLayout->addItem(barsHSpacer);

        labelProgressTitle = new QLabel(cardBarsH);
        labelProgressTitle->setObjectName("labelProgressTitle");

        barsHLayout->addWidget(labelProgressTitle);

        progressBarHackathon = new QProgressBar(cardBarsH);
        progressBarHackathon->setObjectName("progressBarHackathon");
        progressBarHackathon->setMaximum(100);
        progressBarHackathon->setValue(0);

        barsHLayout->addWidget(progressBarHackathon);

        labelProgressNote = new QLabel(cardBarsH);
        labelProgressNote->setObjectName("labelProgressNote");

        barsHLayout->addWidget(labelProgressNote);


        chartsLayout->addWidget(cardBarsH);

        cardBarsV = new QFrame(scrollDashboardContent);
        cardBarsV->setObjectName("cardBarsV");
        cardBarsV->setMinimumSize(QSize(0, 420));
        barsVLayout = new QVBoxLayout(cardBarsV);
        barsVLayout->setSpacing(10);
        barsVLayout->setObjectName("barsVLayout");
        barsVLayout->setContentsMargins(24, 20, 24, 20);
        labelBarsVTitle = new QLabel(cardBarsV);
        labelBarsVTitle->setObjectName("labelBarsVTitle");

        barsVLayout->addWidget(labelBarsVTitle);

        labelBarsVSub = new QLabel(cardBarsV);
        labelBarsVSub->setObjectName("labelBarsVSub");

        barsVLayout->addWidget(labelBarsVSub);

        barsVContainerLayout = new QHBoxLayout();
        barsVContainerLayout->setSpacing(16);
        barsVContainerLayout->setObjectName("barsVContainerLayout");
        barsVContainerLayout->setContentsMargins(0, 0, 0, 0);
        vBar1Layout = new QVBoxLayout();
        vBar1Layout->setObjectName("vBar1Layout");
        barVValue1 = new QLabel(cardBarsV);
        barVValue1->setObjectName("barVValue1");
        barVValue1->setAlignment(Qt::AlignmentFlag::AlignCenter);

        vBar1Layout->addWidget(barVValue1);

        barVBar1 = new QFrame(cardBarsV);
        barVBar1->setObjectName("barVBar1");
        barVBar1->setMinimumSize(QSize(44, 50));
        barVBar1->setMaximumSize(QSize(44, 16777215));

        vBar1Layout->addWidget(barVBar1);

        barVLabel1 = new QLabel(cardBarsV);
        barVLabel1->setObjectName("barVLabel1");
        barVLabel1->setAlignment(Qt::AlignmentFlag::AlignCenter);

        vBar1Layout->addWidget(barVLabel1);


        barsVContainerLayout->addLayout(vBar1Layout);

        vBar2Layout = new QVBoxLayout();
        vBar2Layout->setObjectName("vBar2Layout");
        barVValue2 = new QLabel(cardBarsV);
        barVValue2->setObjectName("barVValue2");
        barVValue2->setAlignment(Qt::AlignmentFlag::AlignCenter);

        vBar2Layout->addWidget(barVValue2);

        barVBar2 = new QFrame(cardBarsV);
        barVBar2->setObjectName("barVBar2");
        barVBar2->setMinimumSize(QSize(44, 50));
        barVBar2->setMaximumSize(QSize(44, 16777215));

        vBar2Layout->addWidget(barVBar2);

        barVLabel2 = new QLabel(cardBarsV);
        barVLabel2->setObjectName("barVLabel2");
        barVLabel2->setAlignment(Qt::AlignmentFlag::AlignCenter);

        vBar2Layout->addWidget(barVLabel2);


        barsVContainerLayout->addLayout(vBar2Layout);

        vBar3Layout = new QVBoxLayout();
        vBar3Layout->setObjectName("vBar3Layout");
        barVValue3 = new QLabel(cardBarsV);
        barVValue3->setObjectName("barVValue3");
        barVValue3->setAlignment(Qt::AlignmentFlag::AlignCenter);

        vBar3Layout->addWidget(barVValue3);

        barVBar3 = new QFrame(cardBarsV);
        barVBar3->setObjectName("barVBar3");
        barVBar3->setMinimumSize(QSize(44, 50));
        barVBar3->setMaximumSize(QSize(44, 16777215));

        vBar3Layout->addWidget(barVBar3);

        barVLabel3 = new QLabel(cardBarsV);
        barVLabel3->setObjectName("barVLabel3");
        barVLabel3->setAlignment(Qt::AlignmentFlag::AlignCenter);

        vBar3Layout->addWidget(barVLabel3);


        barsVContainerLayout->addLayout(vBar3Layout);

        vBar4Layout = new QVBoxLayout();
        vBar4Layout->setObjectName("vBar4Layout");
        barVValue4 = new QLabel(cardBarsV);
        barVValue4->setObjectName("barVValue4");
        barVValue4->setAlignment(Qt::AlignmentFlag::AlignCenter);

        vBar4Layout->addWidget(barVValue4);

        barVBar4 = new QFrame(cardBarsV);
        barVBar4->setObjectName("barVBar4");
        barVBar4->setMinimumSize(QSize(44, 50));
        barVBar4->setMaximumSize(QSize(44, 16777215));

        vBar4Layout->addWidget(barVBar4);

        barVLabel4 = new QLabel(cardBarsV);
        barVLabel4->setObjectName("barVLabel4");
        barVLabel4->setAlignment(Qt::AlignmentFlag::AlignCenter);

        vBar4Layout->addWidget(barVLabel4);


        barsVContainerLayout->addLayout(vBar4Layout);

        vBar5Layout = new QVBoxLayout();
        vBar5Layout->setObjectName("vBar5Layout");
        barVValue5 = new QLabel(cardBarsV);
        barVValue5->setObjectName("barVValue5");
        barVValue5->setAlignment(Qt::AlignmentFlag::AlignCenter);

        vBar5Layout->addWidget(barVValue5);

        barVBar5 = new QFrame(cardBarsV);
        barVBar5->setObjectName("barVBar5");
        barVBar5->setMinimumSize(QSize(44, 50));
        barVBar5->setMaximumSize(QSize(44, 16777215));

        vBar5Layout->addWidget(barVBar5);

        barVLabel5 = new QLabel(cardBarsV);
        barVLabel5->setObjectName("barVLabel5");
        barVLabel5->setAlignment(Qt::AlignmentFlag::AlignCenter);

        vBar5Layout->addWidget(barVLabel5);


        barsVContainerLayout->addLayout(vBar5Layout);

        vBar6Layout = new QVBoxLayout();
        vBar6Layout->setObjectName("vBar6Layout");
        barVValue6 = new QLabel(cardBarsV);
        barVValue6->setObjectName("barVValue6");
        barVValue6->setAlignment(Qt::AlignmentFlag::AlignCenter);

        vBar6Layout->addWidget(barVValue6);

        barVBar6 = new QFrame(cardBarsV);
        barVBar6->setObjectName("barVBar6");
        barVBar6->setMinimumSize(QSize(44, 50));
        barVBar6->setMaximumSize(QSize(44, 16777215));

        vBar6Layout->addWidget(barVBar6);

        barVLabel6 = new QLabel(cardBarsV);
        barVLabel6->setObjectName("barVLabel6");
        barVLabel6->setAlignment(Qt::AlignmentFlag::AlignCenter);

        vBar6Layout->addWidget(barVLabel6);


        barsVContainerLayout->addLayout(vBar6Layout);


        barsVLayout->addLayout(barsVContainerLayout);

        barsVSpacer = new QSpacerItem(20, 20, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        barsVLayout->addItem(barsVSpacer);

        barsVFooterLayout = new QHBoxLayout();
        barsVFooterLayout->setObjectName("barsVFooterLayout");
        labelBarsVFooterLeft = new QLabel(cardBarsV);
        labelBarsVFooterLeft->setObjectName("labelBarsVFooterLeft");

        barsVFooterLayout->addWidget(labelBarsVFooterLeft);

        barsVFooterSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        barsVFooterLayout->addItem(barsVFooterSpacer);

        labelBarsVFooterRight = new QLabel(cardBarsV);
        labelBarsVFooterRight->setObjectName("labelBarsVFooterRight");

        barsVFooterLayout->addWidget(labelBarsVFooterRight);


        barsVLayout->addLayout(barsVFooterLayout);


        chartsLayout->addWidget(cardBarsV);


        dashboardContentLayout->addLayout(chartsLayout);

        cardChatbot = new QFrame(scrollDashboardContent);
        cardChatbot->setObjectName("cardChatbot");
        cardChatbot->setMinimumSize(QSize(0, 500));
        chatbotLayout = new QVBoxLayout(cardChatbot);
        chatbotLayout->setSpacing(12);
        chatbotLayout->setObjectName("chatbotLayout");
        chatbotLayout->setContentsMargins(24, 20, 24, 20);
        chatHeaderLayout = new QHBoxLayout();
        chatHeaderLayout->setObjectName("chatHeaderLayout");
        chatTitle = new QLabel(cardChatbot);
        chatTitle->setObjectName("chatTitle");

        chatHeaderLayout->addWidget(chatTitle);

        chatHeaderSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        chatHeaderLayout->addItem(chatHeaderSpacer);

        chatStatusOnline = new QLabel(cardChatbot);
        chatStatusOnline->setObjectName("chatStatusOnline");
        chatStatusOnline->setAlignment(Qt::AlignmentFlag::AlignCenter);

        chatHeaderLayout->addWidget(chatStatusOnline);


        chatbotLayout->addLayout(chatHeaderLayout);

        chatSub = new QLabel(cardChatbot);
        chatSub->setObjectName("chatSub");

        chatbotLayout->addWidget(chatSub);

        chatContentLayout = new QHBoxLayout();
        chatContentLayout->setSpacing(16);
        chatContentLayout->setObjectName("chatContentLayout");
        chatDisplay = new QTextBrowser(cardChatbot);
        chatDisplay->setObjectName("chatDisplay");
        chatDisplay->setMinimumSize(QSize(0, 320));

        chatContentLayout->addWidget(chatDisplay);

        chatQuickLayout = new QVBoxLayout();
        chatQuickLayout->setSpacing(10);
        chatQuickLayout->setObjectName("chatQuickLayout");
        chatQuickTitle = new QLabel(cardChatbot);
        chatQuickTitle->setObjectName("chatQuickTitle");

        chatQuickLayout->addWidget(chatQuickTitle);

        chatQuick1 = new QPushButton(cardChatbot);
        chatQuick1->setObjectName("chatQuick1");
        chatQuick1->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        chatQuickLayout->addWidget(chatQuick1);

        chatQuick2 = new QPushButton(cardChatbot);
        chatQuick2->setObjectName("chatQuick2");
        chatQuick2->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        chatQuickLayout->addWidget(chatQuick2);

        chatQuick3 = new QPushButton(cardChatbot);
        chatQuick3->setObjectName("chatQuick3");
        chatQuick3->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        chatQuickLayout->addWidget(chatQuick3);

        chatQuick4 = new QPushButton(cardChatbot);
        chatQuick4->setObjectName("chatQuick4");
        chatQuick4->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        chatQuickLayout->addWidget(chatQuick4);

        chatQuickSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        chatQuickLayout->addItem(chatQuickSpacer);


        chatContentLayout->addLayout(chatQuickLayout);


        chatbotLayout->addLayout(chatContentLayout);

        chatInputLayout = new QHBoxLayout();
        chatInputLayout->setObjectName("chatInputLayout");
        chatInput = new QLineEdit(cardChatbot);
        chatInput->setObjectName("chatInput");
        chatInput->setMinimumSize(QSize(0, 48));

        chatInputLayout->addWidget(chatInput);

        chatSendBtn = new QPushButton(cardChatbot);
        chatSendBtn->setObjectName("chatSendBtn");
        chatSendBtn->setMinimumSize(QSize(140, 48));
        chatSendBtn->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        chatInputLayout->addWidget(chatSendBtn);


        chatbotLayout->addLayout(chatInputLayout);


        dashboardContentLayout->addWidget(cardChatbot);

        scrollDashboard->setWidget(scrollDashboardContent);

        dashboardOuterLayout->addWidget(scrollDashboard);

        stackedWidget->addWidget(pageDashboard);
        pageEmployes = new QWidget();
        pageEmployes->setObjectName("pageEmployes");
        employesOuterLayout = new QVBoxLayout(pageEmployes);
        employesOuterLayout->setSpacing(0);
        employesOuterLayout->setObjectName("employesOuterLayout");
        employesOuterLayout->setContentsMargins(0, 0, 0, 0);
        scrollEmployes = new QScrollArea(pageEmployes);
        scrollEmployes->setObjectName("scrollEmployes");
        scrollEmployes->setFrameShape(QFrame::Shape::NoFrame);
        scrollEmployes->setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAsNeeded);
        scrollEmployes->setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAsNeeded);
        scrollEmployes->setWidgetResizable(true);
        scrollEmployesContent = new QWidget();
        scrollEmployesContent->setObjectName("scrollEmployesContent");
        scrollEmployesContent->setGeometry(QRect(0, 0, 1029, 975));
        employesContentLayout = new QVBoxLayout(scrollEmployesContent);
        employesContentLayout->setSpacing(0);
        employesContentLayout->setObjectName("employesContentLayout");
        employesContentLayout->setContentsMargins(0, 0, 0, 0);
        frameNavbarEmployes = new QFrame(scrollEmployesContent);
        frameNavbarEmployes->setObjectName("frameNavbarEmployes");
        frameNavbarEmployes->setMinimumSize(QSize(0, 76));
        frameNavbarEmployes->setMaximumSize(QSize(16777215, 76));
        navbarEmployesLayout = new QHBoxLayout(frameNavbarEmployes);
        navbarEmployesLayout->setSpacing(0);
        navbarEmployesLayout->setObjectName("navbarEmployesLayout");
        navbarEmployesLayout->setContentsMargins(24, 0, 24, 0);
        labelNavLogoEmp = new QLabel(frameNavbarEmployes);
        labelNavLogoEmp->setObjectName("labelNavLogoEmp");
        labelNavLogoEmp->setMinimumSize(QSize(44, 44));
        labelNavLogoEmp->setMaximumSize(QSize(44, 44));
        labelNavLogoEmp->setAlignment(Qt::AlignmentFlag::AlignCenter);

        navbarEmployesLayout->addWidget(labelNavLogoEmp);

        brandEmpLayout = new QVBoxLayout();
        brandEmpLayout->setSpacing(0);
        brandEmpLayout->setObjectName("brandEmpLayout");
        brandEmpLayout->setContentsMargins(12, -1, -1, -1);
        labelNavBrandEmp = new QLabel(frameNavbarEmployes);
        labelNavBrandEmp->setObjectName("labelNavBrandEmp");

        brandEmpLayout->addWidget(labelNavBrandEmp);

        labelNavSubEmp = new QLabel(frameNavbarEmployes);
        labelNavSubEmp->setObjectName("labelNavSubEmp");

        brandEmpLayout->addWidget(labelNavSubEmp);


        navbarEmployesLayout->addLayout(brandEmpLayout);

        frameNavSepEmp = new QFrame(frameNavbarEmployes);
        frameNavSepEmp->setObjectName("frameNavSepEmp");
        frameNavSepEmp->setMinimumSize(QSize(1, 40));
        frameNavSepEmp->setMaximumSize(QSize(1, 40));

        navbarEmployesLayout->addWidget(frameNavSepEmp);

        navDashboardEmployes = new QPushButton(frameNavbarEmployes);
        navDashboardEmployes->setObjectName("navDashboardEmployes");
        navDashboardEmployes->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        navbarEmployesLayout->addWidget(navDashboardEmployes);

        navEmployesEmployes = new QPushButton(frameNavbarEmployes);
        navEmployesEmployes->setObjectName("navEmployesEmployes");
        navEmployesEmployes->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        navbarEmployesLayout->addWidget(navEmployesEmployes);

        navSallesEmployes = new QPushButton(frameNavbarEmployes);
        navSallesEmployes->setObjectName("navSallesEmployes");
        navSallesEmployes->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        navbarEmployesLayout->addWidget(navSallesEmployes);

        navEvaluateursEmployes = new QPushButton(frameNavbarEmployes);
        navEvaluateursEmployes->setObjectName("navEvaluateursEmployes");
        navEvaluateursEmployes->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        navbarEmployesLayout->addWidget(navEvaluateursEmployes);

        navParticipantsEmployes = new QPushButton(frameNavbarEmployes);
        navParticipantsEmployes->setObjectName("navParticipantsEmployes");
        navParticipantsEmployes->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        navbarEmployesLayout->addWidget(navParticipantsEmployes);

        navSponsorsEmployes = new QPushButton(frameNavbarEmployes);
        navSponsorsEmployes->setObjectName("navSponsorsEmployes");
        navSponsorsEmployes->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        navbarEmployesLayout->addWidget(navSponsorsEmployes);

        navProjetsEmployes = new QPushButton(frameNavbarEmployes);
        navProjetsEmployes->setObjectName("navProjetsEmployes");
        navProjetsEmployes->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        navbarEmployesLayout->addWidget(navProjetsEmployes);

        navbarEmpSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        navbarEmployesLayout->addItem(navbarEmpSpacer);

        navDeconnexionEmployes = new QPushButton(frameNavbarEmployes);
        navDeconnexionEmployes->setObjectName("navDeconnexionEmployes");
        navDeconnexionEmployes->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        navbarEmployesLayout->addWidget(navDeconnexionEmployes);


        employesContentLayout->addWidget(frameNavbarEmployes);

        frameTopbarEmployes = new QFrame(scrollEmployesContent);
        frameTopbarEmployes->setObjectName("frameTopbarEmployes");
        frameTopbarEmployes->setMinimumSize(QSize(0, 76));
        frameTopbarEmployes->setMaximumSize(QSize(16777215, 76));
        topbarEmpLayout = new QVBoxLayout(frameTopbarEmployes);
        topbarEmpLayout->setSpacing(2);
        topbarEmpLayout->setObjectName("topbarEmpLayout");
        topbarEmpLayout->setContentsMargins(32, 14, 32, 14);
        topbarTitleEmp = new QLabel(frameTopbarEmployes);
        topbarTitleEmp->setObjectName("topbarTitleEmp");

        topbarEmpLayout->addWidget(topbarTitleEmp);

        topbarSubEmp = new QLabel(frameTopbarEmployes);
        topbarSubEmp->setObjectName("topbarSubEmp");

        topbarEmpLayout->addWidget(topbarSubEmp);


        employesContentLayout->addWidget(frameTopbarEmployes);

        statsEmpLayout = new QHBoxLayout();
        statsEmpLayout->setSpacing(16);
        statsEmpLayout->setObjectName("statsEmpLayout");
        statsEmpLayout->setContentsMargins(32, 20, 32, 20);
        cardEmpStat1 = new QFrame(scrollEmployesContent);
        cardEmpStat1->setObjectName("cardEmpStat1");
        cardEmpStat1->setMinimumSize(QSize(0, 120));
        cardEmpStat1Layout = new QVBoxLayout(cardEmpStat1);
        cardEmpStat1Layout->setSpacing(4);
        cardEmpStat1Layout->setObjectName("cardEmpStat1Layout");
        cardEmpStat1Layout->setContentsMargins(20, 18, 20, 18);
        cardEmpTitle1 = new QLabel(cardEmpStat1);
        cardEmpTitle1->setObjectName("cardEmpTitle1");

        cardEmpStat1Layout->addWidget(cardEmpTitle1);

        cardEmpValue1 = new QLabel(cardEmpStat1);
        cardEmpValue1->setObjectName("cardEmpValue1");

        cardEmpStat1Layout->addWidget(cardEmpValue1);

        cardEmpSub1 = new QLabel(cardEmpStat1);
        cardEmpSub1->setObjectName("cardEmpSub1");

        cardEmpStat1Layout->addWidget(cardEmpSub1);


        statsEmpLayout->addWidget(cardEmpStat1);

        cardEmpStat2 = new QFrame(scrollEmployesContent);
        cardEmpStat2->setObjectName("cardEmpStat2");
        cardEmpStat2->setMinimumSize(QSize(0, 120));
        cardEmpStat2Layout = new QVBoxLayout(cardEmpStat2);
        cardEmpStat2Layout->setSpacing(4);
        cardEmpStat2Layout->setObjectName("cardEmpStat2Layout");
        cardEmpStat2Layout->setContentsMargins(20, 18, 20, 18);
        cardEmpTitle2 = new QLabel(cardEmpStat2);
        cardEmpTitle2->setObjectName("cardEmpTitle2");

        cardEmpStat2Layout->addWidget(cardEmpTitle2);

        cardEmpValue2 = new QLabel(cardEmpStat2);
        cardEmpValue2->setObjectName("cardEmpValue2");

        cardEmpStat2Layout->addWidget(cardEmpValue2);

        cardEmpSub2 = new QLabel(cardEmpStat2);
        cardEmpSub2->setObjectName("cardEmpSub2");

        cardEmpStat2Layout->addWidget(cardEmpSub2);


        statsEmpLayout->addWidget(cardEmpStat2);

        cardEmpStat3 = new QFrame(scrollEmployesContent);
        cardEmpStat3->setObjectName("cardEmpStat3");
        cardEmpStat3->setMinimumSize(QSize(0, 120));
        cardEmpStat3Layout = new QVBoxLayout(cardEmpStat3);
        cardEmpStat3Layout->setSpacing(4);
        cardEmpStat3Layout->setObjectName("cardEmpStat3Layout");
        cardEmpStat3Layout->setContentsMargins(20, 18, 20, 18);
        cardEmpTitle3 = new QLabel(cardEmpStat3);
        cardEmpTitle3->setObjectName("cardEmpTitle3");

        cardEmpStat3Layout->addWidget(cardEmpTitle3);

        cardEmpValue3 = new QLabel(cardEmpStat3);
        cardEmpValue3->setObjectName("cardEmpValue3");

        cardEmpStat3Layout->addWidget(cardEmpValue3);

        cardEmpSub3 = new QLabel(cardEmpStat3);
        cardEmpSub3->setObjectName("cardEmpSub3");

        cardEmpStat3Layout->addWidget(cardEmpSub3);


        statsEmpLayout->addWidget(cardEmpStat3);

        cardEmpStat4 = new QFrame(scrollEmployesContent);
        cardEmpStat4->setObjectName("cardEmpStat4");
        cardEmpStat4->setMinimumSize(QSize(0, 120));
        cardEmpStat4Layout = new QVBoxLayout(cardEmpStat4);
        cardEmpStat4Layout->setSpacing(4);
        cardEmpStat4Layout->setObjectName("cardEmpStat4Layout");
        cardEmpStat4Layout->setContentsMargins(20, 18, 20, 18);
        cardEmpTitle4 = new QLabel(cardEmpStat4);
        cardEmpTitle4->setObjectName("cardEmpTitle4");

        cardEmpStat4Layout->addWidget(cardEmpTitle4);

        cardEmpValue4 = new QLabel(cardEmpStat4);
        cardEmpValue4->setObjectName("cardEmpValue4");

        cardEmpStat4Layout->addWidget(cardEmpValue4);

        cardEmpSub4 = new QLabel(cardEmpStat4);
        cardEmpSub4->setObjectName("cardEmpSub4");

        cardEmpStat4Layout->addWidget(cardEmpSub4);


        statsEmpLayout->addWidget(cardEmpStat4);


        employesContentLayout->addLayout(statsEmpLayout);

        cardFormEmployes = new QFrame(scrollEmployesContent);
        cardFormEmployes->setObjectName("cardFormEmployes");
        cardFormEmployes->setMinimumSize(QSize(0, 220));
        formEmpLayout = new QVBoxLayout(cardFormEmployes);
        formEmpLayout->setSpacing(14);
        formEmpLayout->setObjectName("formEmpLayout");
        formEmpLayout->setContentsMargins(24, 20, 24, 20);
        formTitleEmp = new QLabel(cardFormEmployes);
        formTitleEmp->setObjectName("formTitleEmp");

        formEmpLayout->addWidget(formTitleEmp);

        formEmpGrid = new QGridLayout();
        formEmpGrid->setSpacing(12);
        formEmpGrid->setObjectName("formEmpGrid");
        lblEmpID = new QLabel(cardFormEmployes);
        lblEmpID->setObjectName("lblEmpID");

        formEmpGrid->addWidget(lblEmpID, 0, 0, 1, 1);

        lblEmpNom = new QLabel(cardFormEmployes);
        lblEmpNom->setObjectName("lblEmpNom");

        formEmpGrid->addWidget(lblEmpNom, 0, 1, 1, 1);

        lblEmpPrenom = new QLabel(cardFormEmployes);
        lblEmpPrenom->setObjectName("lblEmpPrenom");

        formEmpGrid->addWidget(lblEmpPrenom, 0, 2, 1, 1);

        lblEmpMdp = new QLabel(cardFormEmployes);
        lblEmpMdp->setObjectName("lblEmpMdp");

        formEmpGrid->addWidget(lblEmpMdp, 0, 3, 1, 1);

        lblEmpRole = new QLabel(cardFormEmployes);
        lblEmpRole->setObjectName("lblEmpRole");

        formEmpGrid->addWidget(lblEmpRole, 0, 4, 1, 1);

        lblEmpStatut = new QLabel(cardFormEmployes);
        lblEmpStatut->setObjectName("lblEmpStatut");

        formEmpGrid->addWidget(lblEmpStatut, 0, 5, 1, 1);

        lineEditEmpID = new QLineEdit(cardFormEmployes);
        lineEditEmpID->setObjectName("lineEditEmpID");
        lineEditEmpID->setReadOnly(true);

        formEmpGrid->addWidget(lineEditEmpID, 1, 0, 1, 1);

        lineEditEmpNom = new QLineEdit(cardFormEmployes);
        lineEditEmpNom->setObjectName("lineEditEmpNom");

        formEmpGrid->addWidget(lineEditEmpNom, 1, 1, 1, 1);

        lineEditEmpPrenom = new QLineEdit(cardFormEmployes);
        lineEditEmpPrenom->setObjectName("lineEditEmpPrenom");

        formEmpGrid->addWidget(lineEditEmpPrenom, 1, 2, 1, 1);

        lineEditEmpMdp = new QLineEdit(cardFormEmployes);
        lineEditEmpMdp->setObjectName("lineEditEmpMdp");
        lineEditEmpMdp->setEchoMode(QLineEdit::EchoMode::Password);

        formEmpGrid->addWidget(lineEditEmpMdp, 1, 3, 1, 1);

        comboBoxEmpRole = new QComboBox(cardFormEmployes);
        comboBoxEmpRole->addItem(QString());
        comboBoxEmpRole->addItem(QString());
        comboBoxEmpRole->addItem(QString());
        comboBoxEmpRole->setObjectName("comboBoxEmpRole");

        formEmpGrid->addWidget(comboBoxEmpRole, 1, 4, 1, 1);

        comboBoxEmpStatut = new QComboBox(cardFormEmployes);
        comboBoxEmpStatut->addItem(QString());
        comboBoxEmpStatut->addItem(QString());
        comboBoxEmpStatut->setObjectName("comboBoxEmpStatut");

        formEmpGrid->addWidget(comboBoxEmpStatut, 1, 5, 1, 1);


        formEmpLayout->addLayout(formEmpGrid);

        formEmpButtonsLayout = new QHBoxLayout();
        formEmpButtonsLayout->setSpacing(12);
        formEmpButtonsLayout->setObjectName("formEmpButtonsLayout");
        btnEmpAjouter = new QPushButton(cardFormEmployes);
        btnEmpAjouter->setObjectName("btnEmpAjouter");
        btnEmpAjouter->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        formEmpButtonsLayout->addWidget(btnEmpAjouter);

        btnEmpModifier = new QPushButton(cardFormEmployes);
        btnEmpModifier->setObjectName("btnEmpModifier");
        btnEmpModifier->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        formEmpButtonsLayout->addWidget(btnEmpModifier);

        btnEmpSupprimer = new QPushButton(cardFormEmployes);
        btnEmpSupprimer->setObjectName("btnEmpSupprimer");
        btnEmpSupprimer->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        formEmpButtonsLayout->addWidget(btnEmpSupprimer);

        btnEmpConsulter = new QPushButton(cardFormEmployes);
        btnEmpConsulter->setObjectName("btnEmpConsulter");
        btnEmpConsulter->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        formEmpButtonsLayout->addWidget(btnEmpConsulter);

        formEmpBtnSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        formEmpButtonsLayout->addItem(formEmpBtnSpacer);


        formEmpLayout->addLayout(formEmpButtonsLayout);


        employesContentLayout->addWidget(cardFormEmployes);

        searchEmpLayout = new QHBoxLayout();
        searchEmpLayout->setSpacing(12);
        searchEmpLayout->setObjectName("searchEmpLayout");
        searchEmpLayout->setContentsMargins(32, 0, 32, 20);
        lineEditRechercheEmployes = new QLineEdit(scrollEmployesContent);
        lineEditRechercheEmployes->setObjectName("lineEditRechercheEmployes");
        lineEditRechercheEmployes->setMinimumSize(QSize(400, 42));

        searchEmpLayout->addWidget(lineEditRechercheEmployes);

        btnEmpRechercher = new QPushButton(scrollEmployesContent);
        btnEmpRechercher->setObjectName("btnEmpRechercher");
        btnEmpRechercher->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        searchEmpLayout->addWidget(btnEmpRechercher);

        btnEmpTrier = new QPushButton(scrollEmployesContent);
        btnEmpTrier->setObjectName("btnEmpTrier");
        btnEmpTrier->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        searchEmpLayout->addWidget(btnEmpTrier);

        searchEmpSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        searchEmpLayout->addItem(searchEmpSpacer);


        employesContentLayout->addLayout(searchEmpLayout);

        cardTableEmployes = new QFrame(scrollEmployesContent);
        cardTableEmployes->setObjectName("cardTableEmployes");
        cardTableEmployes->setMinimumSize(QSize(0, 380));
        tableEmpLayout = new QVBoxLayout(cardTableEmployes);
        tableEmpLayout->setSpacing(12);
        tableEmpLayout->setObjectName("tableEmpLayout");
        tableEmpLayout->setContentsMargins(20, 20, 20, 20);
        tableTitleEmp = new QLabel(cardTableEmployes);
        tableTitleEmp->setObjectName("tableTitleEmp");

        tableEmpLayout->addWidget(tableTitleEmp);

        tableWidgetEmployes = new QTableWidget(cardTableEmployes);
        if (tableWidgetEmployes->columnCount() < 6)
            tableWidgetEmployes->setColumnCount(6);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetEmployes->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetEmployes->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidgetEmployes->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidgetEmployes->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidgetEmployes->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidgetEmployes->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        tableWidgetEmployes->setObjectName("tableWidgetEmployes");
        tableWidgetEmployes->setAlternatingRowColors(true);
        tableWidgetEmployes->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);

        tableEmpLayout->addWidget(tableWidgetEmployes);


        employesContentLayout->addWidget(cardTableEmployes);

        scrollEmployes->setWidget(scrollEmployesContent);

        employesOuterLayout->addWidget(scrollEmployes);

        stackedWidget->addWidget(pageEmployes);
        pageSalles = new QWidget();
        pageSalles->setObjectName("pageSalles");
        sallesOuterLayout = new QVBoxLayout(pageSalles);
        sallesOuterLayout->setSpacing(0);
        sallesOuterLayout->setObjectName("sallesOuterLayout");
        sallesOuterLayout->setContentsMargins(0, 0, 0, 0);
        scrollSalles = new QScrollArea(pageSalles);
        scrollSalles->setObjectName("scrollSalles");
        scrollSalles->setFrameShape(QFrame::Shape::NoFrame);
        scrollSalles->setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAsNeeded);
        scrollSalles->setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAsNeeded);
        scrollSalles->setWidgetResizable(true);
        scrollSallesContent = new QWidget();
        scrollSallesContent->setObjectName("scrollSallesContent");
        scrollSallesContent->setGeometry(QRect(0, 0, 1029, 975));
        sallesContentLayout = new QVBoxLayout(scrollSallesContent);
        sallesContentLayout->setSpacing(0);
        sallesContentLayout->setObjectName("sallesContentLayout");
        sallesContentLayout->setContentsMargins(0, 0, 0, 0);
        frameNavbarSalles = new QFrame(scrollSallesContent);
        frameNavbarSalles->setObjectName("frameNavbarSalles");
        frameNavbarSalles->setMinimumSize(QSize(0, 76));
        frameNavbarSalles->setMaximumSize(QSize(16777215, 76));
        navbarSallesLayout = new QHBoxLayout(frameNavbarSalles);
        navbarSallesLayout->setSpacing(0);
        navbarSallesLayout->setObjectName("navbarSallesLayout");
        navbarSallesLayout->setContentsMargins(24, 0, 24, 0);
        labelNavLogoSalles = new QLabel(frameNavbarSalles);
        labelNavLogoSalles->setObjectName("labelNavLogoSalles");
        labelNavLogoSalles->setMinimumSize(QSize(44, 44));
        labelNavLogoSalles->setMaximumSize(QSize(44, 44));
        labelNavLogoSalles->setAlignment(Qt::AlignmentFlag::AlignCenter);

        navbarSallesLayout->addWidget(labelNavLogoSalles);

        brandSallesLayout = new QVBoxLayout();
        brandSallesLayout->setSpacing(0);
        brandSallesLayout->setObjectName("brandSallesLayout");
        brandSallesLayout->setContentsMargins(12, -1, -1, -1);
        labelNavBrandSalles = new QLabel(frameNavbarSalles);
        labelNavBrandSalles->setObjectName("labelNavBrandSalles");

        brandSallesLayout->addWidget(labelNavBrandSalles);

        labelNavSubSalles = new QLabel(frameNavbarSalles);
        labelNavSubSalles->setObjectName("labelNavSubSalles");

        brandSallesLayout->addWidget(labelNavSubSalles);


        navbarSallesLayout->addLayout(brandSallesLayout);

        frameNavSepSalles = new QFrame(frameNavbarSalles);
        frameNavSepSalles->setObjectName("frameNavSepSalles");
        frameNavSepSalles->setMinimumSize(QSize(1, 40));
        frameNavSepSalles->setMaximumSize(QSize(1, 40));

        navbarSallesLayout->addWidget(frameNavSepSalles);

        navDashboardSalles = new QPushButton(frameNavbarSalles);
        navDashboardSalles->setObjectName("navDashboardSalles");
        navDashboardSalles->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        navbarSallesLayout->addWidget(navDashboardSalles);

        navEmployesSalles = new QPushButton(frameNavbarSalles);
        navEmployesSalles->setObjectName("navEmployesSalles");
        navEmployesSalles->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        navbarSallesLayout->addWidget(navEmployesSalles);

        navSallesSalles = new QPushButton(frameNavbarSalles);
        navSallesSalles->setObjectName("navSallesSalles");
        navSallesSalles->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        navbarSallesLayout->addWidget(navSallesSalles);

        navEvaluateursSalles = new QPushButton(frameNavbarSalles);
        navEvaluateursSalles->setObjectName("navEvaluateursSalles");
        navEvaluateursSalles->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        navbarSallesLayout->addWidget(navEvaluateursSalles);

        navParticipantsSalles = new QPushButton(frameNavbarSalles);
        navParticipantsSalles->setObjectName("navParticipantsSalles");
        navParticipantsSalles->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        navbarSallesLayout->addWidget(navParticipantsSalles);

        navSponsorsSalles = new QPushButton(frameNavbarSalles);
        navSponsorsSalles->setObjectName("navSponsorsSalles");
        navSponsorsSalles->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        navbarSallesLayout->addWidget(navSponsorsSalles);

        navProjetsSalles = new QPushButton(frameNavbarSalles);
        navProjetsSalles->setObjectName("navProjetsSalles");
        navProjetsSalles->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        navbarSallesLayout->addWidget(navProjetsSalles);

        navbarSallesSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        navbarSallesLayout->addItem(navbarSallesSpacer);

        navDeconnexionSalles = new QPushButton(frameNavbarSalles);
        navDeconnexionSalles->setObjectName("navDeconnexionSalles");
        navDeconnexionSalles->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        navbarSallesLayout->addWidget(navDeconnexionSalles);


        sallesContentLayout->addWidget(frameNavbarSalles);

        frameTopbarSalles = new QFrame(scrollSallesContent);
        frameTopbarSalles->setObjectName("frameTopbarSalles");
        frameTopbarSalles->setMinimumSize(QSize(0, 76));
        frameTopbarSalles->setMaximumSize(QSize(16777215, 76));
        topbarSallesLayout = new QVBoxLayout(frameTopbarSalles);
        topbarSallesLayout->setSpacing(2);
        topbarSallesLayout->setObjectName("topbarSallesLayout");
        topbarSallesLayout->setContentsMargins(32, 14, 32, 14);
        topbarTitleSalles = new QLabel(frameTopbarSalles);
        topbarTitleSalles->setObjectName("topbarTitleSalles");

        topbarSallesLayout->addWidget(topbarTitleSalles);

        topbarSubSalles = new QLabel(frameTopbarSalles);
        topbarSubSalles->setObjectName("topbarSubSalles");

        topbarSallesLayout->addWidget(topbarSubSalles);


        sallesContentLayout->addWidget(frameTopbarSalles);

        statsSallesLayout = new QHBoxLayout();
        statsSallesLayout->setSpacing(16);
        statsSallesLayout->setObjectName("statsSallesLayout");
        statsSallesLayout->setContentsMargins(32, 20, 32, 20);
        cardSalleStat1 = new QFrame(scrollSallesContent);
        cardSalleStat1->setObjectName("cardSalleStat1");
        cardSalleStat1->setMinimumSize(QSize(0, 120));
        cardSalleStat1Layout = new QVBoxLayout(cardSalleStat1);
        cardSalleStat1Layout->setSpacing(4);
        cardSalleStat1Layout->setObjectName("cardSalleStat1Layout");
        cardSalleStat1Layout->setContentsMargins(20, 18, 20, 18);
        cardSalleTitle1 = new QLabel(cardSalleStat1);
        cardSalleTitle1->setObjectName("cardSalleTitle1");

        cardSalleStat1Layout->addWidget(cardSalleTitle1);

        cardSalleValue1 = new QLabel(cardSalleStat1);
        cardSalleValue1->setObjectName("cardSalleValue1");

        cardSalleStat1Layout->addWidget(cardSalleValue1);

        cardSalleSub1 = new QLabel(cardSalleStat1);
        cardSalleSub1->setObjectName("cardSalleSub1");

        cardSalleStat1Layout->addWidget(cardSalleSub1);


        statsSallesLayout->addWidget(cardSalleStat1);

        cardSalleStat2 = new QFrame(scrollSallesContent);
        cardSalleStat2->setObjectName("cardSalleStat2");
        cardSalleStat2->setMinimumSize(QSize(0, 120));
        cardSalleStat2Layout = new QVBoxLayout(cardSalleStat2);
        cardSalleStat2Layout->setSpacing(4);
        cardSalleStat2Layout->setObjectName("cardSalleStat2Layout");
        cardSalleStat2Layout->setContentsMargins(20, 18, 20, 18);
        cardSalleTitle2 = new QLabel(cardSalleStat2);
        cardSalleTitle2->setObjectName("cardSalleTitle2");

        cardSalleStat2Layout->addWidget(cardSalleTitle2);

        cardSalleValue2 = new QLabel(cardSalleStat2);
        cardSalleValue2->setObjectName("cardSalleValue2");

        cardSalleStat2Layout->addWidget(cardSalleValue2);

        cardSalleSub2 = new QLabel(cardSalleStat2);
        cardSalleSub2->setObjectName("cardSalleSub2");

        cardSalleStat2Layout->addWidget(cardSalleSub2);


        statsSallesLayout->addWidget(cardSalleStat2);

        cardSalleStat3 = new QFrame(scrollSallesContent);
        cardSalleStat3->setObjectName("cardSalleStat3");
        cardSalleStat3->setMinimumSize(QSize(0, 120));
        cardSalleStat3Layout = new QVBoxLayout(cardSalleStat3);
        cardSalleStat3Layout->setSpacing(4);
        cardSalleStat3Layout->setObjectName("cardSalleStat3Layout");
        cardSalleStat3Layout->setContentsMargins(20, 18, 20, 18);
        cardSalleTitle3 = new QLabel(cardSalleStat3);
        cardSalleTitle3->setObjectName("cardSalleTitle3");

        cardSalleStat3Layout->addWidget(cardSalleTitle3);

        cardSalleValue3 = new QLabel(cardSalleStat3);
        cardSalleValue3->setObjectName("cardSalleValue3");

        cardSalleStat3Layout->addWidget(cardSalleValue3);

        cardSalleSub3 = new QLabel(cardSalleStat3);
        cardSalleSub3->setObjectName("cardSalleSub3");

        cardSalleStat3Layout->addWidget(cardSalleSub3);


        statsSallesLayout->addWidget(cardSalleStat3);

        cardSalleStat4 = new QFrame(scrollSallesContent);
        cardSalleStat4->setObjectName("cardSalleStat4");
        cardSalleStat4->setMinimumSize(QSize(0, 120));
        cardSalleStat4Layout = new QVBoxLayout(cardSalleStat4);
        cardSalleStat4Layout->setSpacing(4);
        cardSalleStat4Layout->setObjectName("cardSalleStat4Layout");
        cardSalleStat4Layout->setContentsMargins(20, 18, 20, 18);
        cardSalleTitle4 = new QLabel(cardSalleStat4);
        cardSalleTitle4->setObjectName("cardSalleTitle4");

        cardSalleStat4Layout->addWidget(cardSalleTitle4);

        cardSalleValue4 = new QLabel(cardSalleStat4);
        cardSalleValue4->setObjectName("cardSalleValue4");

        cardSalleStat4Layout->addWidget(cardSalleValue4);

        cardSalleSub4 = new QLabel(cardSalleStat4);
        cardSalleSub4->setObjectName("cardSalleSub4");

        cardSalleStat4Layout->addWidget(cardSalleSub4);


        statsSallesLayout->addWidget(cardSalleStat4);


        sallesContentLayout->addLayout(statsSallesLayout);

        cardFormSalles = new QFrame(scrollSallesContent);
        cardFormSalles->setObjectName("cardFormSalles");
        cardFormSalles->setMinimumSize(QSize(0, 220));
        formSallesLayout = new QVBoxLayout(cardFormSalles);
        formSallesLayout->setSpacing(14);
        formSallesLayout->setObjectName("formSallesLayout");
        formSallesLayout->setContentsMargins(24, 20, 24, 20);
        formTitleSalles = new QLabel(cardFormSalles);
        formTitleSalles->setObjectName("formTitleSalles");

        formSallesLayout->addWidget(formTitleSalles);

        formSallesGrid = new QGridLayout();
        formSallesGrid->setSpacing(12);
        formSallesGrid->setObjectName("formSallesGrid");
        lblSalleID = new QLabel(cardFormSalles);
        lblSalleID->setObjectName("lblSalleID");

        formSallesGrid->addWidget(lblSalleID, 0, 0, 1, 1);

        lblSalleNom = new QLabel(cardFormSalles);
        lblSalleNom->setObjectName("lblSalleNom");

        formSallesGrid->addWidget(lblSalleNom, 0, 1, 1, 1);

        lblSalleCap = new QLabel(cardFormSalles);
        lblSalleCap->setObjectName("lblSalleCap");

        formSallesGrid->addWidget(lblSalleCap, 0, 2, 1, 1);

        lblSalleType = new QLabel(cardFormSalles);
        lblSalleType->setObjectName("lblSalleType");

        formSallesGrid->addWidget(lblSalleType, 0, 3, 1, 1);

        lblSalleDispo = new QLabel(cardFormSalles);
        lblSalleDispo->setObjectName("lblSalleDispo");

        formSallesGrid->addWidget(lblSalleDispo, 0, 4, 1, 1);

        lineEditSalleID = new QLineEdit(cardFormSalles);
        lineEditSalleID->setObjectName("lineEditSalleID");
        lineEditSalleID->setReadOnly(true);

        formSallesGrid->addWidget(lineEditSalleID, 1, 0, 1, 1);

        lineEditSalleNom = new QLineEdit(cardFormSalles);
        lineEditSalleNom->setObjectName("lineEditSalleNom");

        formSallesGrid->addWidget(lineEditSalleNom, 1, 1, 1, 1);

        spinBoxSalleCapacite = new QSpinBox(cardFormSalles);
        spinBoxSalleCapacite->setObjectName("spinBoxSalleCapacite");
        spinBoxSalleCapacite->setMaximum(9999);

        formSallesGrid->addWidget(spinBoxSalleCapacite, 1, 2, 1, 1);

        comboBoxSalleType = new QComboBox(cardFormSalles);
        comboBoxSalleType->addItem(QString());
        comboBoxSalleType->addItem(QString());
        comboBoxSalleType->addItem(QString());
        comboBoxSalleType->addItem(QString());
        comboBoxSalleType->setObjectName("comboBoxSalleType");

        formSallesGrid->addWidget(comboBoxSalleType, 1, 3, 1, 1);

        comboBoxSalleDispo = new QComboBox(cardFormSalles);
        comboBoxSalleDispo->addItem(QString());
        comboBoxSalleDispo->addItem(QString());
        comboBoxSalleDispo->addItem(QString());
        comboBoxSalleDispo->setObjectName("comboBoxSalleDispo");

        formSallesGrid->addWidget(comboBoxSalleDispo, 1, 4, 1, 1);


        formSallesLayout->addLayout(formSallesGrid);

        formSallesButtonsLayout = new QHBoxLayout();
        formSallesButtonsLayout->setSpacing(12);
        formSallesButtonsLayout->setObjectName("formSallesButtonsLayout");
        btnSalleAjouter = new QPushButton(cardFormSalles);
        btnSalleAjouter->setObjectName("btnSalleAjouter");
        btnSalleAjouter->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        formSallesButtonsLayout->addWidget(btnSalleAjouter);

        btnSalleModifier = new QPushButton(cardFormSalles);
        btnSalleModifier->setObjectName("btnSalleModifier");
        btnSalleModifier->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        formSallesButtonsLayout->addWidget(btnSalleModifier);

        btnSalleSupprimer = new QPushButton(cardFormSalles);
        btnSalleSupprimer->setObjectName("btnSalleSupprimer");
        btnSalleSupprimer->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        formSallesButtonsLayout->addWidget(btnSalleSupprimer);

        btnSalleConsulter = new QPushButton(cardFormSalles);
        btnSalleConsulter->setObjectName("btnSalleConsulter");
        btnSalleConsulter->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        formSallesButtonsLayout->addWidget(btnSalleConsulter);

        formSallesBtnSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        formSallesButtonsLayout->addItem(formSallesBtnSpacer);


        formSallesLayout->addLayout(formSallesButtonsLayout);


        sallesContentLayout->addWidget(cardFormSalles);

        searchSallesLayout = new QHBoxLayout();
        searchSallesLayout->setSpacing(12);
        searchSallesLayout->setObjectName("searchSallesLayout");
        searchSallesLayout->setContentsMargins(32, 0, 32, 20);
        lineEditRechercheSalle = new QLineEdit(scrollSallesContent);
        lineEditRechercheSalle->setObjectName("lineEditRechercheSalle");
        lineEditRechercheSalle->setMinimumSize(QSize(400, 42));

        searchSallesLayout->addWidget(lineEditRechercheSalle);

        btnSalleRechercher = new QPushButton(scrollSallesContent);
        btnSalleRechercher->setObjectName("btnSalleRechercher");
        btnSalleRechercher->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        searchSallesLayout->addWidget(btnSalleRechercher);

        btnSalleTrier = new QPushButton(scrollSallesContent);
        btnSalleTrier->setObjectName("btnSalleTrier");
        btnSalleTrier->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        searchSallesLayout->addWidget(btnSalleTrier);

        searchSallesSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        searchSallesLayout->addItem(searchSallesSpacer);


        sallesContentLayout->addLayout(searchSallesLayout);

        cardTableSalles = new QFrame(scrollSallesContent);
        cardTableSalles->setObjectName("cardTableSalles");
        cardTableSalles->setMinimumSize(QSize(0, 380));
        tableSallesLayout = new QVBoxLayout(cardTableSalles);
        tableSallesLayout->setSpacing(12);
        tableSallesLayout->setObjectName("tableSallesLayout");
        tableSallesLayout->setContentsMargins(20, 20, 20, 20);
        tableTitleSalles = new QLabel(cardTableSalles);
        tableTitleSalles->setObjectName("tableTitleSalles");

        tableSallesLayout->addWidget(tableTitleSalles);

        tableWidgetSalles = new QTableWidget(cardTableSalles);
        if (tableWidgetSalles->columnCount() < 6)
            tableWidgetSalles->setColumnCount(6);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidgetSalles->setHorizontalHeaderItem(0, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidgetSalles->setHorizontalHeaderItem(1, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tableWidgetSalles->setHorizontalHeaderItem(2, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        tableWidgetSalles->setHorizontalHeaderItem(3, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        tableWidgetSalles->setHorizontalHeaderItem(4, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        tableWidgetSalles->setHorizontalHeaderItem(5, __qtablewidgetitem11);
        tableWidgetSalles->setObjectName("tableWidgetSalles");
        tableWidgetSalles->setAlternatingRowColors(true);
        tableWidgetSalles->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);

        tableSallesLayout->addWidget(tableWidgetSalles);


        sallesContentLayout->addWidget(cardTableSalles);

        scrollSalles->setWidget(scrollSallesContent);

        sallesOuterLayout->addWidget(scrollSalles);

        stackedWidget->addWidget(pageSalles);
        pageEvaluateurs = new QWidget();
        pageEvaluateurs->setObjectName("pageEvaluateurs");
        evaluateursOuterLayout = new QVBoxLayout(pageEvaluateurs);
        evaluateursOuterLayout->setSpacing(0);
        evaluateursOuterLayout->setObjectName("evaluateursOuterLayout");
        evaluateursOuterLayout->setContentsMargins(0, 0, 0, 0);
        scrollEvaluateurs = new QScrollArea(pageEvaluateurs);
        scrollEvaluateurs->setObjectName("scrollEvaluateurs");
        scrollEvaluateurs->setFrameShape(QFrame::Shape::NoFrame);
        scrollEvaluateurs->setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAsNeeded);
        scrollEvaluateurs->setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAsNeeded);
        scrollEvaluateurs->setWidgetResizable(true);
        scrollEvaluateursContent = new QWidget();
        scrollEvaluateursContent->setObjectName("scrollEvaluateursContent");
        scrollEvaluateursContent->setGeometry(QRect(0, 0, 1029, 975));
        evaluateursContentLayout = new QVBoxLayout(scrollEvaluateursContent);
        evaluateursContentLayout->setSpacing(0);
        evaluateursContentLayout->setObjectName("evaluateursContentLayout");
        evaluateursContentLayout->setContentsMargins(0, 0, 0, 0);
        frameNavbarEvaluateurs = new QFrame(scrollEvaluateursContent);
        frameNavbarEvaluateurs->setObjectName("frameNavbarEvaluateurs");
        frameNavbarEvaluateurs->setMinimumSize(QSize(0, 76));
        frameNavbarEvaluateurs->setMaximumSize(QSize(16777215, 76));
        navbarEvalLayout = new QHBoxLayout(frameNavbarEvaluateurs);
        navbarEvalLayout->setSpacing(0);
        navbarEvalLayout->setObjectName("navbarEvalLayout");
        navbarEvalLayout->setContentsMargins(24, 0, 24, 0);
        sbLogoEval = new QLabel(frameNavbarEvaluateurs);
        sbLogoEval->setObjectName("sbLogoEval");
        sbLogoEval->setMinimumSize(QSize(44, 44));
        sbLogoEval->setMaximumSize(QSize(44, 44));
        sbLogoEval->setAlignment(Qt::AlignmentFlag::AlignCenter);

        navbarEvalLayout->addWidget(sbLogoEval);

        brandEvalLayout = new QVBoxLayout();
        brandEvalLayout->setSpacing(0);
        brandEvalLayout->setObjectName("brandEvalLayout");
        brandEvalLayout->setContentsMargins(12, -1, -1, -1);
        sbBrandEval = new QLabel(frameNavbarEvaluateurs);
        sbBrandEval->setObjectName("sbBrandEval");

        brandEvalLayout->addWidget(sbBrandEval);

        sbSubEval = new QLabel(frameNavbarEvaluateurs);
        sbSubEval->setObjectName("sbSubEval");

        brandEvalLayout->addWidget(sbSubEval);


        navbarEvalLayout->addLayout(brandEvalLayout);

        sbSepEval = new QFrame(frameNavbarEvaluateurs);
        sbSepEval->setObjectName("sbSepEval");
        sbSepEval->setMinimumSize(QSize(1, 40));
        sbSepEval->setMaximumSize(QSize(1, 40));

        navbarEvalLayout->addWidget(sbSepEval);

        navDashboardEvaluateurs = new QPushButton(frameNavbarEvaluateurs);
        navDashboardEvaluateurs->setObjectName("navDashboardEvaluateurs");
        navDashboardEvaluateurs->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        navbarEvalLayout->addWidget(navDashboardEvaluateurs);

        navEmployesEvaluateurs = new QPushButton(frameNavbarEvaluateurs);
        navEmployesEvaluateurs->setObjectName("navEmployesEvaluateurs");
        navEmployesEvaluateurs->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        navbarEvalLayout->addWidget(navEmployesEvaluateurs);

        navSallesEvaluateurs = new QPushButton(frameNavbarEvaluateurs);
        navSallesEvaluateurs->setObjectName("navSallesEvaluateurs");
        navSallesEvaluateurs->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        navbarEvalLayout->addWidget(navSallesEvaluateurs);

        navEvaluateursEvaluateurs = new QPushButton(frameNavbarEvaluateurs);
        navEvaluateursEvaluateurs->setObjectName("navEvaluateursEvaluateurs");
        navEvaluateursEvaluateurs->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        navbarEvalLayout->addWidget(navEvaluateursEvaluateurs);

        navParticipantsEvaluateurs = new QPushButton(frameNavbarEvaluateurs);
        navParticipantsEvaluateurs->setObjectName("navParticipantsEvaluateurs");
        navParticipantsEvaluateurs->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        navbarEvalLayout->addWidget(navParticipantsEvaluateurs);

        navSponsorsEvaluateurs = new QPushButton(frameNavbarEvaluateurs);
        navSponsorsEvaluateurs->setObjectName("navSponsorsEvaluateurs");
        navSponsorsEvaluateurs->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        navbarEvalLayout->addWidget(navSponsorsEvaluateurs);

        navProjetsEvaluateurs = new QPushButton(frameNavbarEvaluateurs);
        navProjetsEvaluateurs->setObjectName("navProjetsEvaluateurs");
        navProjetsEvaluateurs->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        navbarEvalLayout->addWidget(navProjetsEvaluateurs);

        navbarEvalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        navbarEvalLayout->addItem(navbarEvalSpacer);

        navDeconnexionEvaluateurs = new QPushButton(frameNavbarEvaluateurs);
        navDeconnexionEvaluateurs->setObjectName("navDeconnexionEvaluateurs");
        navDeconnexionEvaluateurs->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        navbarEvalLayout->addWidget(navDeconnexionEvaluateurs);


        evaluateursContentLayout->addWidget(frameNavbarEvaluateurs);

        frameTopbarEvaluateurs = new QFrame(scrollEvaluateursContent);
        frameTopbarEvaluateurs->setObjectName("frameTopbarEvaluateurs");
        frameTopbarEvaluateurs->setMinimumSize(QSize(0, 76));
        frameTopbarEvaluateurs->setMaximumSize(QSize(16777215, 76));
        topbarEvalLayout = new QVBoxLayout(frameTopbarEvaluateurs);
        topbarEvalLayout->setSpacing(2);
        topbarEvalLayout->setObjectName("topbarEvalLayout");
        topbarEvalLayout->setContentsMargins(32, 14, 32, 14);
        topbarTitleEval = new QLabel(frameTopbarEvaluateurs);
        topbarTitleEval->setObjectName("topbarTitleEval");

        topbarEvalLayout->addWidget(topbarTitleEval);

        topbarSubEval = new QLabel(frameTopbarEvaluateurs);
        topbarSubEval->setObjectName("topbarSubEval");

        topbarEvalLayout->addWidget(topbarSubEval);


        evaluateursContentLayout->addWidget(frameTopbarEvaluateurs);

        statsEvalLayout = new QHBoxLayout();
        statsEvalLayout->setSpacing(16);
        statsEvalLayout->setObjectName("statsEvalLayout");
        statsEvalLayout->setContentsMargins(32, 20, 32, 20);
        cardEvalStat1 = new QFrame(scrollEvaluateursContent);
        cardEvalStat1->setObjectName("cardEvalStat1");
        cardEvalStat1->setMinimumSize(QSize(0, 120));
        cardEvalStat1Layout = new QVBoxLayout(cardEvalStat1);
        cardEvalStat1Layout->setSpacing(4);
        cardEvalStat1Layout->setObjectName("cardEvalStat1Layout");
        cardEvalStat1Layout->setContentsMargins(20, 18, 20, 18);
        cardEvalTitle1 = new QLabel(cardEvalStat1);
        cardEvalTitle1->setObjectName("cardEvalTitle1");

        cardEvalStat1Layout->addWidget(cardEvalTitle1);

        cardEvalValue1 = new QLabel(cardEvalStat1);
        cardEvalValue1->setObjectName("cardEvalValue1");

        cardEvalStat1Layout->addWidget(cardEvalValue1);

        cardEvalSub1 = new QLabel(cardEvalStat1);
        cardEvalSub1->setObjectName("cardEvalSub1");

        cardEvalStat1Layout->addWidget(cardEvalSub1);


        statsEvalLayout->addWidget(cardEvalStat1);

        cardEvalStat2 = new QFrame(scrollEvaluateursContent);
        cardEvalStat2->setObjectName("cardEvalStat2");
        cardEvalStat2->setMinimumSize(QSize(0, 120));
        cardEvalStat2Layout = new QVBoxLayout(cardEvalStat2);
        cardEvalStat2Layout->setSpacing(4);
        cardEvalStat2Layout->setObjectName("cardEvalStat2Layout");
        cardEvalStat2Layout->setContentsMargins(20, 18, 20, 18);
        cardEvalTitle2 = new QLabel(cardEvalStat2);
        cardEvalTitle2->setObjectName("cardEvalTitle2");

        cardEvalStat2Layout->addWidget(cardEvalTitle2);

        cardEvalValue2 = new QLabel(cardEvalStat2);
        cardEvalValue2->setObjectName("cardEvalValue2");

        cardEvalStat2Layout->addWidget(cardEvalValue2);

        cardEvalSub2 = new QLabel(cardEvalStat2);
        cardEvalSub2->setObjectName("cardEvalSub2");

        cardEvalStat2Layout->addWidget(cardEvalSub2);


        statsEvalLayout->addWidget(cardEvalStat2);

        cardEvalStat3 = new QFrame(scrollEvaluateursContent);
        cardEvalStat3->setObjectName("cardEvalStat3");
        cardEvalStat3->setMinimumSize(QSize(0, 120));
        cardEvalStat3Layout = new QVBoxLayout(cardEvalStat3);
        cardEvalStat3Layout->setSpacing(4);
        cardEvalStat3Layout->setObjectName("cardEvalStat3Layout");
        cardEvalStat3Layout->setContentsMargins(20, 18, 20, 18);
        cardEvalTitle3 = new QLabel(cardEvalStat3);
        cardEvalTitle3->setObjectName("cardEvalTitle3");

        cardEvalStat3Layout->addWidget(cardEvalTitle3);

        cardEvalValue3 = new QLabel(cardEvalStat3);
        cardEvalValue3->setObjectName("cardEvalValue3");

        cardEvalStat3Layout->addWidget(cardEvalValue3);

        cardEvalSub3 = new QLabel(cardEvalStat3);
        cardEvalSub3->setObjectName("cardEvalSub3");

        cardEvalStat3Layout->addWidget(cardEvalSub3);


        statsEvalLayout->addWidget(cardEvalStat3);


        evaluateursContentLayout->addLayout(statsEvalLayout);

        cardFormEvaluateurs = new QFrame(scrollEvaluateursContent);
        cardFormEvaluateurs->setObjectName("cardFormEvaluateurs");
        cardFormEvaluateurs->setMinimumSize(QSize(0, 220));
        formEvalLayout = new QVBoxLayout(cardFormEvaluateurs);
        formEvalLayout->setSpacing(14);
        formEvalLayout->setObjectName("formEvalLayout");
        formEvalLayout->setContentsMargins(24, 20, 24, 20);
        formTitleEval = new QLabel(cardFormEvaluateurs);
        formTitleEval->setObjectName("formTitleEval");

        formEvalLayout->addWidget(formTitleEval);

        formEvalGrid = new QGridLayout();
        formEvalGrid->setSpacing(12);
        formEvalGrid->setObjectName("formEvalGrid");
        lblEvalID = new QLabel(cardFormEvaluateurs);
        lblEvalID->setObjectName("lblEvalID");

        formEvalGrid->addWidget(lblEvalID, 0, 0, 1, 1);

        lblEvalNom = new QLabel(cardFormEvaluateurs);
        lblEvalNom->setObjectName("lblEvalNom");

        formEvalGrid->addWidget(lblEvalNom, 0, 1, 1, 1);

        lblEvalPrenom = new QLabel(cardFormEvaluateurs);
        lblEvalPrenom->setObjectName("lblEvalPrenom");

        formEvalGrid->addWidget(lblEvalPrenom, 0, 2, 1, 1);

        lblEvalEmail = new QLabel(cardFormEvaluateurs);
        lblEvalEmail->setObjectName("lblEvalEmail");

        formEvalGrid->addWidget(lblEvalEmail, 0, 3, 1, 1);

        lblEvalStatut = new QLabel(cardFormEvaluateurs);
        lblEvalStatut->setObjectName("lblEvalStatut");

        formEvalGrid->addWidget(lblEvalStatut, 0, 4, 1, 1);

        lineEditEvalID = new QLineEdit(cardFormEvaluateurs);
        lineEditEvalID->setObjectName("lineEditEvalID");
        lineEditEvalID->setReadOnly(true);

        formEvalGrid->addWidget(lineEditEvalID, 1, 0, 1, 1);

        lineEditEvalNom = new QLineEdit(cardFormEvaluateurs);
        lineEditEvalNom->setObjectName("lineEditEvalNom");

        formEvalGrid->addWidget(lineEditEvalNom, 1, 1, 1, 1);

        lineEditEvalPrenom = new QLineEdit(cardFormEvaluateurs);
        lineEditEvalPrenom->setObjectName("lineEditEvalPrenom");

        formEvalGrid->addWidget(lineEditEvalPrenom, 1, 2, 1, 1);

        lineEditEvalEmail = new QLineEdit(cardFormEvaluateurs);
        lineEditEvalEmail->setObjectName("lineEditEvalEmail");

        formEvalGrid->addWidget(lineEditEvalEmail, 1, 3, 1, 1);

        comboBoxEvalStatut = new QComboBox(cardFormEvaluateurs);
        comboBoxEvalStatut->addItem(QString());
        comboBoxEvalStatut->addItem(QString());
        comboBoxEvalStatut->setObjectName("comboBoxEvalStatut");

        formEvalGrid->addWidget(comboBoxEvalStatut, 1, 4, 1, 1);


        formEvalLayout->addLayout(formEvalGrid);

        formEvalButtonsLayout = new QHBoxLayout();
        formEvalButtonsLayout->setSpacing(12);
        formEvalButtonsLayout->setObjectName("formEvalButtonsLayout");
        btnEvalAjouter = new QPushButton(cardFormEvaluateurs);
        btnEvalAjouter->setObjectName("btnEvalAjouter");
        btnEvalAjouter->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        formEvalButtonsLayout->addWidget(btnEvalAjouter);

        btnEvalModifier = new QPushButton(cardFormEvaluateurs);
        btnEvalModifier->setObjectName("btnEvalModifier");
        btnEvalModifier->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        formEvalButtonsLayout->addWidget(btnEvalModifier);

        btnEvalSupprimer = new QPushButton(cardFormEvaluateurs);
        btnEvalSupprimer->setObjectName("btnEvalSupprimer");
        btnEvalSupprimer->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        formEvalButtonsLayout->addWidget(btnEvalSupprimer);

        btnEvalConsulter = new QPushButton(cardFormEvaluateurs);
        btnEvalConsulter->setObjectName("btnEvalConsulter");
        btnEvalConsulter->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        formEvalButtonsLayout->addWidget(btnEvalConsulter);

        formEvalBtnSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        formEvalButtonsLayout->addItem(formEvalBtnSpacer);


        formEvalLayout->addLayout(formEvalButtonsLayout);


        evaluateursContentLayout->addWidget(cardFormEvaluateurs);

        searchEvalLayout = new QHBoxLayout();
        searchEvalLayout->setSpacing(12);
        searchEvalLayout->setObjectName("searchEvalLayout");
        searchEvalLayout->setContentsMargins(32, 0, 32, 20);
        lineEditRechercheEval = new QLineEdit(scrollEvaluateursContent);
        lineEditRechercheEval->setObjectName("lineEditRechercheEval");
        lineEditRechercheEval->setMinimumSize(QSize(400, 42));

        searchEvalLayout->addWidget(lineEditRechercheEval);

        btnEvalRechercher = new QPushButton(scrollEvaluateursContent);
        btnEvalRechercher->setObjectName("btnEvalRechercher");
        btnEvalRechercher->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        searchEvalLayout->addWidget(btnEvalRechercher);

        btnEvalTrier = new QPushButton(scrollEvaluateursContent);
        btnEvalTrier->setObjectName("btnEvalTrier");
        btnEvalTrier->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        searchEvalLayout->addWidget(btnEvalTrier);

        searchEvalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        searchEvalLayout->addItem(searchEvalSpacer);


        evaluateursContentLayout->addLayout(searchEvalLayout);

        cardTableEvaluateurs = new QFrame(scrollEvaluateursContent);
        cardTableEvaluateurs->setObjectName("cardTableEvaluateurs");
        cardTableEvaluateurs->setMinimumSize(QSize(0, 380));
        tableEvalLayout = new QVBoxLayout(cardTableEvaluateurs);
        tableEvalLayout->setSpacing(12);
        tableEvalLayout->setObjectName("tableEvalLayout");
        tableEvalLayout->setContentsMargins(20, 20, 20, 20);
        tableTitleEval = new QLabel(cardTableEvaluateurs);
        tableTitleEval->setObjectName("tableTitleEval");

        tableEvalLayout->addWidget(tableTitleEval);

        tableWidgetEvaluateurs = new QTableWidget(cardTableEvaluateurs);
        if (tableWidgetEvaluateurs->columnCount() < 6)
            tableWidgetEvaluateurs->setColumnCount(6);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        tableWidgetEvaluateurs->setHorizontalHeaderItem(0, __qtablewidgetitem12);
        QTableWidgetItem *__qtablewidgetitem13 = new QTableWidgetItem();
        tableWidgetEvaluateurs->setHorizontalHeaderItem(1, __qtablewidgetitem13);
        QTableWidgetItem *__qtablewidgetitem14 = new QTableWidgetItem();
        tableWidgetEvaluateurs->setHorizontalHeaderItem(2, __qtablewidgetitem14);
        QTableWidgetItem *__qtablewidgetitem15 = new QTableWidgetItem();
        tableWidgetEvaluateurs->setHorizontalHeaderItem(3, __qtablewidgetitem15);
        QTableWidgetItem *__qtablewidgetitem16 = new QTableWidgetItem();
        tableWidgetEvaluateurs->setHorizontalHeaderItem(4, __qtablewidgetitem16);
        QTableWidgetItem *__qtablewidgetitem17 = new QTableWidgetItem();
        tableWidgetEvaluateurs->setHorizontalHeaderItem(5, __qtablewidgetitem17);
        tableWidgetEvaluateurs->setObjectName("tableWidgetEvaluateurs");
        tableWidgetEvaluateurs->setAlternatingRowColors(true);
        tableWidgetEvaluateurs->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);

        tableEvalLayout->addWidget(tableWidgetEvaluateurs);


        evaluateursContentLayout->addWidget(cardTableEvaluateurs);

        scrollEvaluateurs->setWidget(scrollEvaluateursContent);

        evaluateursOuterLayout->addWidget(scrollEvaluateurs);

        stackedWidget->addWidget(pageEvaluateurs);
        pageParticipants = new QWidget();
        pageParticipants->setObjectName("pageParticipants");
        participantsOuterLayout = new QVBoxLayout(pageParticipants);
        participantsOuterLayout->setSpacing(0);
        participantsOuterLayout->setObjectName("participantsOuterLayout");
        participantsOuterLayout->setContentsMargins(0, 0, 0, 0);
        scrollParticipants = new QScrollArea(pageParticipants);
        scrollParticipants->setObjectName("scrollParticipants");
        scrollParticipants->setFrameShape(QFrame::Shape::NoFrame);
        scrollParticipants->setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAsNeeded);
        scrollParticipants->setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAsNeeded);
        scrollParticipants->setWidgetResizable(true);
        scrollParticipantsContent = new QWidget();
        scrollParticipantsContent->setObjectName("scrollParticipantsContent");
        scrollParticipantsContent->setGeometry(QRect(0, 0, 1029, 975));
        participantsContentLayout = new QVBoxLayout(scrollParticipantsContent);
        participantsContentLayout->setSpacing(0);
        participantsContentLayout->setObjectName("participantsContentLayout");
        participantsContentLayout->setContentsMargins(0, 0, 0, 0);
        frameNavbarParticipants = new QFrame(scrollParticipantsContent);
        frameNavbarParticipants->setObjectName("frameNavbarParticipants");
        frameNavbarParticipants->setMinimumSize(QSize(0, 76));
        frameNavbarParticipants->setMaximumSize(QSize(16777215, 76));
        navbarPartLayout = new QHBoxLayout(frameNavbarParticipants);
        navbarPartLayout->setSpacing(0);
        navbarPartLayout->setObjectName("navbarPartLayout");
        navbarPartLayout->setContentsMargins(24, 0, 24, 0);
        sbLogoPart = new QLabel(frameNavbarParticipants);
        sbLogoPart->setObjectName("sbLogoPart");
        sbLogoPart->setMinimumSize(QSize(44, 44));
        sbLogoPart->setMaximumSize(QSize(44, 44));
        sbLogoPart->setAlignment(Qt::AlignmentFlag::AlignCenter);

        navbarPartLayout->addWidget(sbLogoPart);

        brandPartLayout = new QVBoxLayout();
        brandPartLayout->setSpacing(0);
        brandPartLayout->setObjectName("brandPartLayout");
        brandPartLayout->setContentsMargins(12, -1, -1, -1);
        sbBrandPart = new QLabel(frameNavbarParticipants);
        sbBrandPart->setObjectName("sbBrandPart");

        brandPartLayout->addWidget(sbBrandPart);

        sbSubPart = new QLabel(frameNavbarParticipants);
        sbSubPart->setObjectName("sbSubPart");

        brandPartLayout->addWidget(sbSubPart);


        navbarPartLayout->addLayout(brandPartLayout);

        sbSepPart = new QFrame(frameNavbarParticipants);
        sbSepPart->setObjectName("sbSepPart");
        sbSepPart->setMinimumSize(QSize(1, 40));
        sbSepPart->setMaximumSize(QSize(1, 40));

        navbarPartLayout->addWidget(sbSepPart);

        navDashboardParticipants = new QPushButton(frameNavbarParticipants);
        navDashboardParticipants->setObjectName("navDashboardParticipants");
        navDashboardParticipants->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        navbarPartLayout->addWidget(navDashboardParticipants);

        navEmployesParticipants = new QPushButton(frameNavbarParticipants);
        navEmployesParticipants->setObjectName("navEmployesParticipants");
        navEmployesParticipants->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        navbarPartLayout->addWidget(navEmployesParticipants);

        navSallesParticipants = new QPushButton(frameNavbarParticipants);
        navSallesParticipants->setObjectName("navSallesParticipants");
        navSallesParticipants->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        navbarPartLayout->addWidget(navSallesParticipants);

        navEvaluateursParticipants = new QPushButton(frameNavbarParticipants);
        navEvaluateursParticipants->setObjectName("navEvaluateursParticipants");
        navEvaluateursParticipants->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        navbarPartLayout->addWidget(navEvaluateursParticipants);

        navParticipantsParticipants = new QPushButton(frameNavbarParticipants);
        navParticipantsParticipants->setObjectName("navParticipantsParticipants");
        navParticipantsParticipants->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        navbarPartLayout->addWidget(navParticipantsParticipants);

        navSponsorsParticipants = new QPushButton(frameNavbarParticipants);
        navSponsorsParticipants->setObjectName("navSponsorsParticipants");
        navSponsorsParticipants->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        navbarPartLayout->addWidget(navSponsorsParticipants);

        navProjetsParticipants = new QPushButton(frameNavbarParticipants);
        navProjetsParticipants->setObjectName("navProjetsParticipants");
        navProjetsParticipants->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        navbarPartLayout->addWidget(navProjetsParticipants);

        navbarPartSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        navbarPartLayout->addItem(navbarPartSpacer);

        navDeconnexionParticipants = new QPushButton(frameNavbarParticipants);
        navDeconnexionParticipants->setObjectName("navDeconnexionParticipants");
        navDeconnexionParticipants->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        navbarPartLayout->addWidget(navDeconnexionParticipants);


        participantsContentLayout->addWidget(frameNavbarParticipants);

        frameTopbarParticipants = new QFrame(scrollParticipantsContent);
        frameTopbarParticipants->setObjectName("frameTopbarParticipants");
        frameTopbarParticipants->setMinimumSize(QSize(0, 76));
        frameTopbarParticipants->setMaximumSize(QSize(16777215, 76));
        topbarPartLayout = new QVBoxLayout(frameTopbarParticipants);
        topbarPartLayout->setSpacing(2);
        topbarPartLayout->setObjectName("topbarPartLayout");
        topbarPartLayout->setContentsMargins(32, 14, 32, 14);
        topbarTitlePart = new QLabel(frameTopbarParticipants);
        topbarTitlePart->setObjectName("topbarTitlePart");

        topbarPartLayout->addWidget(topbarTitlePart);

        topbarSubPart = new QLabel(frameTopbarParticipants);
        topbarSubPart->setObjectName("topbarSubPart");

        topbarPartLayout->addWidget(topbarSubPart);


        participantsContentLayout->addWidget(frameTopbarParticipants);

        statsPartLayout = new QHBoxLayout();
        statsPartLayout->setSpacing(16);
        statsPartLayout->setObjectName("statsPartLayout");
        statsPartLayout->setContentsMargins(32, 20, 32, 20);
        cardPartStat1 = new QFrame(scrollParticipantsContent);
        cardPartStat1->setObjectName("cardPartStat1");
        cardPartStat1->setMinimumSize(QSize(0, 120));
        cardPartStat1Layout = new QVBoxLayout(cardPartStat1);
        cardPartStat1Layout->setSpacing(4);
        cardPartStat1Layout->setObjectName("cardPartStat1Layout");
        cardPartStat1Layout->setContentsMargins(20, 18, 20, 18);
        cardPartTitle1 = new QLabel(cardPartStat1);
        cardPartTitle1->setObjectName("cardPartTitle1");

        cardPartStat1Layout->addWidget(cardPartTitle1);

        cardPartValue1 = new QLabel(cardPartStat1);
        cardPartValue1->setObjectName("cardPartValue1");

        cardPartStat1Layout->addWidget(cardPartValue1);

        cardPartSub1 = new QLabel(cardPartStat1);
        cardPartSub1->setObjectName("cardPartSub1");

        cardPartStat1Layout->addWidget(cardPartSub1);


        statsPartLayout->addWidget(cardPartStat1);

        cardPartStat2 = new QFrame(scrollParticipantsContent);
        cardPartStat2->setObjectName("cardPartStat2");
        cardPartStat2->setMinimumSize(QSize(0, 120));
        cardPartStat2Layout = new QVBoxLayout(cardPartStat2);
        cardPartStat2Layout->setSpacing(4);
        cardPartStat2Layout->setObjectName("cardPartStat2Layout");
        cardPartStat2Layout->setContentsMargins(20, 18, 20, 18);
        cardPartTitle2 = new QLabel(cardPartStat2);
        cardPartTitle2->setObjectName("cardPartTitle2");

        cardPartStat2Layout->addWidget(cardPartTitle2);

        cardPartValue2 = new QLabel(cardPartStat2);
        cardPartValue2->setObjectName("cardPartValue2");

        cardPartStat2Layout->addWidget(cardPartValue2);

        cardPartSub2 = new QLabel(cardPartStat2);
        cardPartSub2->setObjectName("cardPartSub2");

        cardPartStat2Layout->addWidget(cardPartSub2);


        statsPartLayout->addWidget(cardPartStat2);

        cardPartStat3 = new QFrame(scrollParticipantsContent);
        cardPartStat3->setObjectName("cardPartStat3");
        cardPartStat3->setMinimumSize(QSize(0, 120));
        cardPartStat3Layout = new QVBoxLayout(cardPartStat3);
        cardPartStat3Layout->setSpacing(4);
        cardPartStat3Layout->setObjectName("cardPartStat3Layout");
        cardPartStat3Layout->setContentsMargins(20, 18, 20, 18);
        cardPartTitle3 = new QLabel(cardPartStat3);
        cardPartTitle3->setObjectName("cardPartTitle3");

        cardPartStat3Layout->addWidget(cardPartTitle3);

        cardPartValue3 = new QLabel(cardPartStat3);
        cardPartValue3->setObjectName("cardPartValue3");

        cardPartStat3Layout->addWidget(cardPartValue3);

        cardPartSub3 = new QLabel(cardPartStat3);
        cardPartSub3->setObjectName("cardPartSub3");

        cardPartStat3Layout->addWidget(cardPartSub3);


        statsPartLayout->addWidget(cardPartStat3);


        participantsContentLayout->addLayout(statsPartLayout);

        cardFormParticipants = new QFrame(scrollParticipantsContent);
        cardFormParticipants->setObjectName("cardFormParticipants");
        cardFormParticipants->setMinimumSize(QSize(0, 220));
        formPartLayout = new QVBoxLayout(cardFormParticipants);
        formPartLayout->setSpacing(14);
        formPartLayout->setObjectName("formPartLayout");
        formPartLayout->setContentsMargins(24, 20, 24, 20);
        formTitlePart = new QLabel(cardFormParticipants);
        formTitlePart->setObjectName("formTitlePart");

        formPartLayout->addWidget(formTitlePart);

        formPartGrid = new QGridLayout();
        formPartGrid->setSpacing(12);
        formPartGrid->setObjectName("formPartGrid");
        lblPartID = new QLabel(cardFormParticipants);
        lblPartID->setObjectName("lblPartID");

        formPartGrid->addWidget(lblPartID, 0, 0, 1, 1);

        lblPartNom = new QLabel(cardFormParticipants);
        lblPartNom->setObjectName("lblPartNom");

        formPartGrid->addWidget(lblPartNom, 0, 1, 1, 1);

        lblPartPrenom = new QLabel(cardFormParticipants);
        lblPartPrenom->setObjectName("lblPartPrenom");

        formPartGrid->addWidget(lblPartPrenom, 0, 2, 1, 1);

        lblPartEmail = new QLabel(cardFormParticipants);
        lblPartEmail->setObjectName("lblPartEmail");

        formPartGrid->addWidget(lblPartEmail, 0, 3, 1, 1);

        lblPartTel = new QLabel(cardFormParticipants);
        lblPartTel->setObjectName("lblPartTel");

        formPartGrid->addWidget(lblPartTel, 0, 4, 1, 1);

        lblPartEquipe = new QLabel(cardFormParticipants);
        lblPartEquipe->setObjectName("lblPartEquipe");

        formPartGrid->addWidget(lblPartEquipe, 0, 5, 1, 1);

        lineEditPartID = new QLineEdit(cardFormParticipants);
        lineEditPartID->setObjectName("lineEditPartID");
        lineEditPartID->setReadOnly(true);

        formPartGrid->addWidget(lineEditPartID, 1, 0, 1, 1);

        lineEditPartNom = new QLineEdit(cardFormParticipants);
        lineEditPartNom->setObjectName("lineEditPartNom");

        formPartGrid->addWidget(lineEditPartNom, 1, 1, 1, 1);

        lineEditPartPrenom = new QLineEdit(cardFormParticipants);
        lineEditPartPrenom->setObjectName("lineEditPartPrenom");

        formPartGrid->addWidget(lineEditPartPrenom, 1, 2, 1, 1);

        lineEditPartEmail = new QLineEdit(cardFormParticipants);
        lineEditPartEmail->setObjectName("lineEditPartEmail");

        formPartGrid->addWidget(lineEditPartEmail, 1, 3, 1, 1);

        lineEditPartTel = new QLineEdit(cardFormParticipants);
        lineEditPartTel->setObjectName("lineEditPartTel");

        formPartGrid->addWidget(lineEditPartTel, 1, 4, 1, 1);

        lineEditPartEquipe = new QLineEdit(cardFormParticipants);
        lineEditPartEquipe->setObjectName("lineEditPartEquipe");

        formPartGrid->addWidget(lineEditPartEquipe, 1, 5, 1, 1);


        formPartLayout->addLayout(formPartGrid);

        formPartButtonsLayout = new QHBoxLayout();
        formPartButtonsLayout->setSpacing(12);
        formPartButtonsLayout->setObjectName("formPartButtonsLayout");
        btnPartAjouter = new QPushButton(cardFormParticipants);
        btnPartAjouter->setObjectName("btnPartAjouter");
        btnPartAjouter->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        formPartButtonsLayout->addWidget(btnPartAjouter);

        btnPartModifier = new QPushButton(cardFormParticipants);
        btnPartModifier->setObjectName("btnPartModifier");
        btnPartModifier->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        formPartButtonsLayout->addWidget(btnPartModifier);

        btnPartSupprimer = new QPushButton(cardFormParticipants);
        btnPartSupprimer->setObjectName("btnPartSupprimer");
        btnPartSupprimer->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        formPartButtonsLayout->addWidget(btnPartSupprimer);

        btnPartConsulter = new QPushButton(cardFormParticipants);
        btnPartConsulter->setObjectName("btnPartConsulter");
        btnPartConsulter->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        formPartButtonsLayout->addWidget(btnPartConsulter);

        formPartBtnSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        formPartButtonsLayout->addItem(formPartBtnSpacer);


        formPartLayout->addLayout(formPartButtonsLayout);


        participantsContentLayout->addWidget(cardFormParticipants);

        searchPartLayout = new QHBoxLayout();
        searchPartLayout->setSpacing(12);
        searchPartLayout->setObjectName("searchPartLayout");
        searchPartLayout->setContentsMargins(32, 0, 32, 20);
        lineEditRecherchePart = new QLineEdit(scrollParticipantsContent);
        lineEditRecherchePart->setObjectName("lineEditRecherchePart");
        lineEditRecherchePart->setMinimumSize(QSize(400, 42));

        searchPartLayout->addWidget(lineEditRecherchePart);

        btnPartRechercher = new QPushButton(scrollParticipantsContent);
        btnPartRechercher->setObjectName("btnPartRechercher");
        btnPartRechercher->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        searchPartLayout->addWidget(btnPartRechercher);

        btnPartTrier = new QPushButton(scrollParticipantsContent);
        btnPartTrier->setObjectName("btnPartTrier");
        btnPartTrier->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        searchPartLayout->addWidget(btnPartTrier);

        searchPartSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        searchPartLayout->addItem(searchPartSpacer);


        participantsContentLayout->addLayout(searchPartLayout);

        cardTableParticipants = new QFrame(scrollParticipantsContent);
        cardTableParticipants->setObjectName("cardTableParticipants");
        cardTableParticipants->setMinimumSize(QSize(0, 380));
        tablePartLayout = new QVBoxLayout(cardTableParticipants);
        tablePartLayout->setSpacing(12);
        tablePartLayout->setObjectName("tablePartLayout");
        tablePartLayout->setContentsMargins(20, 20, 20, 20);
        tableTitlePart = new QLabel(cardTableParticipants);
        tableTitlePart->setObjectName("tableTitlePart");

        tablePartLayout->addWidget(tableTitlePart);

        tableWidgetParticipants = new QTableWidget(cardTableParticipants);
        if (tableWidgetParticipants->columnCount() < 8)
            tableWidgetParticipants->setColumnCount(8);
        QTableWidgetItem *__qtablewidgetitem18 = new QTableWidgetItem();
        tableWidgetParticipants->setHorizontalHeaderItem(0, __qtablewidgetitem18);
        QTableWidgetItem *__qtablewidgetitem19 = new QTableWidgetItem();
        tableWidgetParticipants->setHorizontalHeaderItem(1, __qtablewidgetitem19);
        QTableWidgetItem *__qtablewidgetitem20 = new QTableWidgetItem();
        tableWidgetParticipants->setHorizontalHeaderItem(2, __qtablewidgetitem20);
        QTableWidgetItem *__qtablewidgetitem21 = new QTableWidgetItem();
        tableWidgetParticipants->setHorizontalHeaderItem(3, __qtablewidgetitem21);
        QTableWidgetItem *__qtablewidgetitem22 = new QTableWidgetItem();
        tableWidgetParticipants->setHorizontalHeaderItem(4, __qtablewidgetitem22);
        QTableWidgetItem *__qtablewidgetitem23 = new QTableWidgetItem();
        tableWidgetParticipants->setHorizontalHeaderItem(5, __qtablewidgetitem23);
        QTableWidgetItem *__qtablewidgetitem24 = new QTableWidgetItem();
        tableWidgetParticipants->setHorizontalHeaderItem(6, __qtablewidgetitem24);
        QTableWidgetItem *__qtablewidgetitem25 = new QTableWidgetItem();
        tableWidgetParticipants->setHorizontalHeaderItem(7, __qtablewidgetitem25);
        tableWidgetParticipants->setObjectName("tableWidgetParticipants");
        tableWidgetParticipants->setAlternatingRowColors(true);
        tableWidgetParticipants->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);

        tablePartLayout->addWidget(tableWidgetParticipants);


        participantsContentLayout->addWidget(cardTableParticipants);

        scrollParticipants->setWidget(scrollParticipantsContent);

        participantsOuterLayout->addWidget(scrollParticipants);

        stackedWidget->addWidget(pageParticipants);
        pageSponsors = new QWidget();
        pageSponsors->setObjectName("pageSponsors");
        sponsorsOuterLayout = new QVBoxLayout(pageSponsors);
        sponsorsOuterLayout->setSpacing(0);
        sponsorsOuterLayout->setObjectName("sponsorsOuterLayout");
        sponsorsOuterLayout->setContentsMargins(0, 0, 0, 0);
        scrollSponsors = new QScrollArea(pageSponsors);
        scrollSponsors->setObjectName("scrollSponsors");
        scrollSponsors->setFrameShape(QFrame::Shape::NoFrame);
        scrollSponsors->setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAsNeeded);
        scrollSponsors->setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAsNeeded);
        scrollSponsors->setWidgetResizable(true);
        scrollSponsorsContent = new QWidget();
        scrollSponsorsContent->setObjectName("scrollSponsorsContent");
        scrollSponsorsContent->setGeometry(QRect(0, 0, 1029, 975));
        sponsorsContentLayout = new QVBoxLayout(scrollSponsorsContent);
        sponsorsContentLayout->setSpacing(0);
        sponsorsContentLayout->setObjectName("sponsorsContentLayout");
        sponsorsContentLayout->setContentsMargins(0, 0, 0, 0);
        frameNavbarSponsors = new QFrame(scrollSponsorsContent);
        frameNavbarSponsors->setObjectName("frameNavbarSponsors");
        frameNavbarSponsors->setMinimumSize(QSize(0, 76));
        frameNavbarSponsors->setMaximumSize(QSize(16777215, 76));
        navbarSponLayout = new QHBoxLayout(frameNavbarSponsors);
        navbarSponLayout->setSpacing(0);
        navbarSponLayout->setObjectName("navbarSponLayout");
        navbarSponLayout->setContentsMargins(24, 0, 24, 0);
        sbLogoSpon = new QLabel(frameNavbarSponsors);
        sbLogoSpon->setObjectName("sbLogoSpon");
        sbLogoSpon->setMinimumSize(QSize(44, 44));
        sbLogoSpon->setMaximumSize(QSize(44, 44));
        sbLogoSpon->setAlignment(Qt::AlignmentFlag::AlignCenter);

        navbarSponLayout->addWidget(sbLogoSpon);

        brandSponLayout = new QVBoxLayout();
        brandSponLayout->setSpacing(0);
        brandSponLayout->setObjectName("brandSponLayout");
        brandSponLayout->setContentsMargins(12, -1, -1, -1);
        sbBrandSpon = new QLabel(frameNavbarSponsors);
        sbBrandSpon->setObjectName("sbBrandSpon");

        brandSponLayout->addWidget(sbBrandSpon);

        sbSubSpon = new QLabel(frameNavbarSponsors);
        sbSubSpon->setObjectName("sbSubSpon");

        brandSponLayout->addWidget(sbSubSpon);


        navbarSponLayout->addLayout(brandSponLayout);

        sbSepSpon = new QFrame(frameNavbarSponsors);
        sbSepSpon->setObjectName("sbSepSpon");
        sbSepSpon->setMinimumSize(QSize(1, 40));
        sbSepSpon->setMaximumSize(QSize(1, 40));

        navbarSponLayout->addWidget(sbSepSpon);

        navDashboardSponsors = new QPushButton(frameNavbarSponsors);
        navDashboardSponsors->setObjectName("navDashboardSponsors");
        navDashboardSponsors->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        navbarSponLayout->addWidget(navDashboardSponsors);

        navEmployesSponsors = new QPushButton(frameNavbarSponsors);
        navEmployesSponsors->setObjectName("navEmployesSponsors");
        navEmployesSponsors->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        navbarSponLayout->addWidget(navEmployesSponsors);

        navSallesSponsors = new QPushButton(frameNavbarSponsors);
        navSallesSponsors->setObjectName("navSallesSponsors");
        navSallesSponsors->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        navbarSponLayout->addWidget(navSallesSponsors);

        navEvaluateursSponsors = new QPushButton(frameNavbarSponsors);
        navEvaluateursSponsors->setObjectName("navEvaluateursSponsors");
        navEvaluateursSponsors->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        navbarSponLayout->addWidget(navEvaluateursSponsors);

        navParticipantsSponsors = new QPushButton(frameNavbarSponsors);
        navParticipantsSponsors->setObjectName("navParticipantsSponsors");
        navParticipantsSponsors->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        navbarSponLayout->addWidget(navParticipantsSponsors);

        navSponsorsSponsors = new QPushButton(frameNavbarSponsors);
        navSponsorsSponsors->setObjectName("navSponsorsSponsors");
        navSponsorsSponsors->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        navbarSponLayout->addWidget(navSponsorsSponsors);

        navProjetsSponsors = new QPushButton(frameNavbarSponsors);
        navProjetsSponsors->setObjectName("navProjetsSponsors");
        navProjetsSponsors->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        navbarSponLayout->addWidget(navProjetsSponsors);

        navbarSponSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        navbarSponLayout->addItem(navbarSponSpacer);

        navDeconnexionSponsors = new QPushButton(frameNavbarSponsors);
        navDeconnexionSponsors->setObjectName("navDeconnexionSponsors");
        navDeconnexionSponsors->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        navbarSponLayout->addWidget(navDeconnexionSponsors);


        sponsorsContentLayout->addWidget(frameNavbarSponsors);

        frameTopbarSponsors = new QFrame(scrollSponsorsContent);
        frameTopbarSponsors->setObjectName("frameTopbarSponsors");
        frameTopbarSponsors->setMinimumSize(QSize(0, 76));
        frameTopbarSponsors->setMaximumSize(QSize(16777215, 76));
        topbarSponLayout = new QVBoxLayout(frameTopbarSponsors);
        topbarSponLayout->setSpacing(2);
        topbarSponLayout->setObjectName("topbarSponLayout");
        topbarSponLayout->setContentsMargins(32, 14, 32, 14);
        topbarTitleSpon = new QLabel(frameTopbarSponsors);
        topbarTitleSpon->setObjectName("topbarTitleSpon");

        topbarSponLayout->addWidget(topbarTitleSpon);

        topbarSubSpon = new QLabel(frameTopbarSponsors);
        topbarSubSpon->setObjectName("topbarSubSpon");

        topbarSponLayout->addWidget(topbarSubSpon);


        sponsorsContentLayout->addWidget(frameTopbarSponsors);

        statsSponLayout = new QHBoxLayout();
        statsSponLayout->setSpacing(16);
        statsSponLayout->setObjectName("statsSponLayout");
        statsSponLayout->setContentsMargins(32, 20, 32, 20);
        cardSponStat1 = new QFrame(scrollSponsorsContent);
        cardSponStat1->setObjectName("cardSponStat1");
        cardSponStat1->setMinimumSize(QSize(0, 120));
        cardSponStat1Layout = new QVBoxLayout(cardSponStat1);
        cardSponStat1Layout->setSpacing(4);
        cardSponStat1Layout->setObjectName("cardSponStat1Layout");
        cardSponStat1Layout->setContentsMargins(20, 18, 20, 18);
        cardSponTitle1 = new QLabel(cardSponStat1);
        cardSponTitle1->setObjectName("cardSponTitle1");

        cardSponStat1Layout->addWidget(cardSponTitle1);

        cardSponValue1 = new QLabel(cardSponStat1);
        cardSponValue1->setObjectName("cardSponValue1");

        cardSponStat1Layout->addWidget(cardSponValue1);

        cardSponSub1 = new QLabel(cardSponStat1);
        cardSponSub1->setObjectName("cardSponSub1");

        cardSponStat1Layout->addWidget(cardSponSub1);


        statsSponLayout->addWidget(cardSponStat1);

        cardSponStat2 = new QFrame(scrollSponsorsContent);
        cardSponStat2->setObjectName("cardSponStat2");
        cardSponStat2->setMinimumSize(QSize(0, 120));
        cardSponStat2Layout = new QVBoxLayout(cardSponStat2);
        cardSponStat2Layout->setSpacing(4);
        cardSponStat2Layout->setObjectName("cardSponStat2Layout");
        cardSponStat2Layout->setContentsMargins(20, 18, 20, 18);
        cardSponTitle2 = new QLabel(cardSponStat2);
        cardSponTitle2->setObjectName("cardSponTitle2");

        cardSponStat2Layout->addWidget(cardSponTitle2);

        cardSponValue2 = new QLabel(cardSponStat2);
        cardSponValue2->setObjectName("cardSponValue2");

        cardSponStat2Layout->addWidget(cardSponValue2);

        cardSponSub2 = new QLabel(cardSponStat2);
        cardSponSub2->setObjectName("cardSponSub2");

        cardSponStat2Layout->addWidget(cardSponSub2);


        statsSponLayout->addWidget(cardSponStat2);

        cardSponStat3 = new QFrame(scrollSponsorsContent);
        cardSponStat3->setObjectName("cardSponStat3");
        cardSponStat3->setMinimumSize(QSize(0, 120));
        cardSponStat3Layout = new QVBoxLayout(cardSponStat3);
        cardSponStat3Layout->setSpacing(4);
        cardSponStat3Layout->setObjectName("cardSponStat3Layout");
        cardSponStat3Layout->setContentsMargins(20, 18, 20, 18);
        cardSponTitle3 = new QLabel(cardSponStat3);
        cardSponTitle3->setObjectName("cardSponTitle3");

        cardSponStat3Layout->addWidget(cardSponTitle3);

        cardSponValue3 = new QLabel(cardSponStat3);
        cardSponValue3->setObjectName("cardSponValue3");

        cardSponStat3Layout->addWidget(cardSponValue3);

        cardSponSub3 = new QLabel(cardSponStat3);
        cardSponSub3->setObjectName("cardSponSub3");

        cardSponStat3Layout->addWidget(cardSponSub3);


        statsSponLayout->addWidget(cardSponStat3);


        sponsorsContentLayout->addLayout(statsSponLayout);

        cardFormSponsors = new QFrame(scrollSponsorsContent);
        cardFormSponsors->setObjectName("cardFormSponsors");
        cardFormSponsors->setMinimumSize(QSize(0, 220));
        formSponLayout = new QVBoxLayout(cardFormSponsors);
        formSponLayout->setSpacing(14);
        formSponLayout->setObjectName("formSponLayout");
        formSponLayout->setContentsMargins(24, 20, 24, 20);
        formTitleSpon = new QLabel(cardFormSponsors);
        formTitleSpon->setObjectName("formTitleSpon");

        formSponLayout->addWidget(formTitleSpon);

        formSponGrid = new QGridLayout();
        formSponGrid->setSpacing(12);
        formSponGrid->setObjectName("formSponGrid");
        lblSponID = new QLabel(cardFormSponsors);
        lblSponID->setObjectName("lblSponID");

        formSponGrid->addWidget(lblSponID, 0, 0, 1, 1);

        lblSponEntreprise = new QLabel(cardFormSponsors);
        lblSponEntreprise->setObjectName("lblSponEntreprise");

        formSponGrid->addWidget(lblSponEntreprise, 0, 1, 1, 1);

        lblSponContact = new QLabel(cardFormSponsors);
        lblSponContact->setObjectName("lblSponContact");

        formSponGrid->addWidget(lblSponContact, 0, 2, 1, 1);

        lblSponType = new QLabel(cardFormSponsors);
        lblSponType->setObjectName("lblSponType");

        formSponGrid->addWidget(lblSponType, 0, 3, 1, 1);

        lblSponStatut = new QLabel(cardFormSponsors);
        lblSponStatut->setObjectName("lblSponStatut");

        formSponGrid->addWidget(lblSponStatut, 0, 4, 1, 1);

        lineEditSponID = new QLineEdit(cardFormSponsors);
        lineEditSponID->setObjectName("lineEditSponID");
        lineEditSponID->setReadOnly(true);

        formSponGrid->addWidget(lineEditSponID, 1, 0, 1, 1);

        lineEditSponEntreprise = new QLineEdit(cardFormSponsors);
        lineEditSponEntreprise->setObjectName("lineEditSponEntreprise");

        formSponGrid->addWidget(lineEditSponEntreprise, 1, 1, 1, 1);

        lineEditSponContact = new QLineEdit(cardFormSponsors);
        lineEditSponContact->setObjectName("lineEditSponContact");

        formSponGrid->addWidget(lineEditSponContact, 1, 2, 1, 1);

        comboBoxSponType = new QComboBox(cardFormSponsors);
        comboBoxSponType->addItem(QString());
        comboBoxSponType->addItem(QString());
        comboBoxSponType->addItem(QString());
        comboBoxSponType->setObjectName("comboBoxSponType");

        formSponGrid->addWidget(comboBoxSponType, 1, 3, 1, 1);

        comboBoxSponStatut = new QComboBox(cardFormSponsors);
        comboBoxSponStatut->addItem(QString());
        comboBoxSponStatut->addItem(QString());
        comboBoxSponStatut->setObjectName("comboBoxSponStatut");

        formSponGrid->addWidget(comboBoxSponStatut, 1, 4, 1, 1);


        formSponLayout->addLayout(formSponGrid);

        formSponButtonsLayout = new QHBoxLayout();
        formSponButtonsLayout->setSpacing(12);
        formSponButtonsLayout->setObjectName("formSponButtonsLayout");
        btnSponAjouter = new QPushButton(cardFormSponsors);
        btnSponAjouter->setObjectName("btnSponAjouter");
        btnSponAjouter->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        formSponButtonsLayout->addWidget(btnSponAjouter);

        btnSponModifier = new QPushButton(cardFormSponsors);
        btnSponModifier->setObjectName("btnSponModifier");
        btnSponModifier->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        formSponButtonsLayout->addWidget(btnSponModifier);

        btnSponSupprimer = new QPushButton(cardFormSponsors);
        btnSponSupprimer->setObjectName("btnSponSupprimer");
        btnSponSupprimer->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        formSponButtonsLayout->addWidget(btnSponSupprimer);

        btnSponConsulter = new QPushButton(cardFormSponsors);
        btnSponConsulter->setObjectName("btnSponConsulter");
        btnSponConsulter->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        formSponButtonsLayout->addWidget(btnSponConsulter);

        formSponBtnSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        formSponButtonsLayout->addItem(formSponBtnSpacer);


        formSponLayout->addLayout(formSponButtonsLayout);


        sponsorsContentLayout->addWidget(cardFormSponsors);

        searchSponLayout = new QHBoxLayout();
        searchSponLayout->setSpacing(12);
        searchSponLayout->setObjectName("searchSponLayout");
        searchSponLayout->setContentsMargins(32, 0, 32, 20);
        lineEditRechercheSpon = new QLineEdit(scrollSponsorsContent);
        lineEditRechercheSpon->setObjectName("lineEditRechercheSpon");
        lineEditRechercheSpon->setMinimumSize(QSize(400, 42));

        searchSponLayout->addWidget(lineEditRechercheSpon);

        btnSponRechercher = new QPushButton(scrollSponsorsContent);
        btnSponRechercher->setObjectName("btnSponRechercher");
        btnSponRechercher->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        searchSponLayout->addWidget(btnSponRechercher);

        btnSponTrier = new QPushButton(scrollSponsorsContent);
        btnSponTrier->setObjectName("btnSponTrier");
        btnSponTrier->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        searchSponLayout->addWidget(btnSponTrier);

        searchSponSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        searchSponLayout->addItem(searchSponSpacer);


        sponsorsContentLayout->addLayout(searchSponLayout);

        cardTableSponsors = new QFrame(scrollSponsorsContent);
        cardTableSponsors->setObjectName("cardTableSponsors");
        cardTableSponsors->setMinimumSize(QSize(0, 380));
        tableSponLayout = new QVBoxLayout(cardTableSponsors);
        tableSponLayout->setSpacing(12);
        tableSponLayout->setObjectName("tableSponLayout");
        tableSponLayout->setContentsMargins(20, 20, 20, 20);
        tableTitleSpon = new QLabel(cardTableSponsors);
        tableTitleSpon->setObjectName("tableTitleSpon");

        tableSponLayout->addWidget(tableTitleSpon);

        tableWidgetSponsors = new QTableWidget(cardTableSponsors);
        if (tableWidgetSponsors->columnCount() < 6)
            tableWidgetSponsors->setColumnCount(6);
        QTableWidgetItem *__qtablewidgetitem26 = new QTableWidgetItem();
        tableWidgetSponsors->setHorizontalHeaderItem(0, __qtablewidgetitem26);
        QTableWidgetItem *__qtablewidgetitem27 = new QTableWidgetItem();
        tableWidgetSponsors->setHorizontalHeaderItem(1, __qtablewidgetitem27);
        QTableWidgetItem *__qtablewidgetitem28 = new QTableWidgetItem();
        tableWidgetSponsors->setHorizontalHeaderItem(2, __qtablewidgetitem28);
        QTableWidgetItem *__qtablewidgetitem29 = new QTableWidgetItem();
        tableWidgetSponsors->setHorizontalHeaderItem(3, __qtablewidgetitem29);
        QTableWidgetItem *__qtablewidgetitem30 = new QTableWidgetItem();
        tableWidgetSponsors->setHorizontalHeaderItem(4, __qtablewidgetitem30);
        QTableWidgetItem *__qtablewidgetitem31 = new QTableWidgetItem();
        tableWidgetSponsors->setHorizontalHeaderItem(5, __qtablewidgetitem31);
        tableWidgetSponsors->setObjectName("tableWidgetSponsors");
        tableWidgetSponsors->setAlternatingRowColors(true);
        tableWidgetSponsors->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);

        tableSponLayout->addWidget(tableWidgetSponsors);


        sponsorsContentLayout->addWidget(cardTableSponsors);

        scrollSponsors->setWidget(scrollSponsorsContent);

        sponsorsOuterLayout->addWidget(scrollSponsors);

        stackedWidget->addWidget(pageSponsors);
        pageProjets = new QWidget();
        pageProjets->setObjectName("pageProjets");
        projetsOuterLayout = new QVBoxLayout(pageProjets);
        projetsOuterLayout->setSpacing(0);
        projetsOuterLayout->setObjectName("projetsOuterLayout");
        projetsOuterLayout->setContentsMargins(0, 0, 0, 0);
        scrollProjets = new QScrollArea(pageProjets);
        scrollProjets->setObjectName("scrollProjets");
        scrollProjets->setFrameShape(QFrame::Shape::NoFrame);
        scrollProjets->setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAsNeeded);
        scrollProjets->setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAsNeeded);
        scrollProjets->setWidgetResizable(true);
        scrollProjetsContent = new QWidget();
        scrollProjetsContent->setObjectName("scrollProjetsContent");
        scrollProjetsContent->setGeometry(QRect(0, 0, 1029, 975));
        projetsContentLayout = new QVBoxLayout(scrollProjetsContent);
        projetsContentLayout->setSpacing(0);
        projetsContentLayout->setObjectName("projetsContentLayout");
        projetsContentLayout->setContentsMargins(0, 0, 0, 0);
        frameNavbarProjets = new QFrame(scrollProjetsContent);
        frameNavbarProjets->setObjectName("frameNavbarProjets");
        frameNavbarProjets->setMinimumSize(QSize(0, 76));
        frameNavbarProjets->setMaximumSize(QSize(16777215, 76));
        navbarProjLayout = new QHBoxLayout(frameNavbarProjets);
        navbarProjLayout->setSpacing(0);
        navbarProjLayout->setObjectName("navbarProjLayout");
        navbarProjLayout->setContentsMargins(24, 0, 24, 0);
        sbLogoProj = new QLabel(frameNavbarProjets);
        sbLogoProj->setObjectName("sbLogoProj");
        sbLogoProj->setMinimumSize(QSize(44, 44));
        sbLogoProj->setMaximumSize(QSize(44, 44));
        sbLogoProj->setAlignment(Qt::AlignmentFlag::AlignCenter);

        navbarProjLayout->addWidget(sbLogoProj);

        brandProjLayout = new QVBoxLayout();
        brandProjLayout->setSpacing(0);
        brandProjLayout->setObjectName("brandProjLayout");
        brandProjLayout->setContentsMargins(12, -1, -1, -1);
        sbBrandProj = new QLabel(frameNavbarProjets);
        sbBrandProj->setObjectName("sbBrandProj");

        brandProjLayout->addWidget(sbBrandProj);

        sbSubProj = new QLabel(frameNavbarProjets);
        sbSubProj->setObjectName("sbSubProj");

        brandProjLayout->addWidget(sbSubProj);


        navbarProjLayout->addLayout(brandProjLayout);

        sbSepProj = new QFrame(frameNavbarProjets);
        sbSepProj->setObjectName("sbSepProj");
        sbSepProj->setMinimumSize(QSize(1, 40));
        sbSepProj->setMaximumSize(QSize(1, 40));

        navbarProjLayout->addWidget(sbSepProj);

        navDashboardProjets = new QPushButton(frameNavbarProjets);
        navDashboardProjets->setObjectName("navDashboardProjets");
        navDashboardProjets->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        navbarProjLayout->addWidget(navDashboardProjets);

        navEmployesProjets = new QPushButton(frameNavbarProjets);
        navEmployesProjets->setObjectName("navEmployesProjets");
        navEmployesProjets->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        navbarProjLayout->addWidget(navEmployesProjets);

        navSallesProjets = new QPushButton(frameNavbarProjets);
        navSallesProjets->setObjectName("navSallesProjets");
        navSallesProjets->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        navbarProjLayout->addWidget(navSallesProjets);

        navEvaluateursProjets = new QPushButton(frameNavbarProjets);
        navEvaluateursProjets->setObjectName("navEvaluateursProjets");
        navEvaluateursProjets->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        navbarProjLayout->addWidget(navEvaluateursProjets);

        navParticipantsProjets = new QPushButton(frameNavbarProjets);
        navParticipantsProjets->setObjectName("navParticipantsProjets");
        navParticipantsProjets->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        navbarProjLayout->addWidget(navParticipantsProjets);

        navSponsorsProjets = new QPushButton(frameNavbarProjets);
        navSponsorsProjets->setObjectName("navSponsorsProjets");
        navSponsorsProjets->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        navbarProjLayout->addWidget(navSponsorsProjets);

        navProjetsProjets = new QPushButton(frameNavbarProjets);
        navProjetsProjets->setObjectName("navProjetsProjets");
        navProjetsProjets->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        navbarProjLayout->addWidget(navProjetsProjets);

        navbarProjSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        navbarProjLayout->addItem(navbarProjSpacer);

        navDeconnexionProjets = new QPushButton(frameNavbarProjets);
        navDeconnexionProjets->setObjectName("navDeconnexionProjets");
        navDeconnexionProjets->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        navbarProjLayout->addWidget(navDeconnexionProjets);


        projetsContentLayout->addWidget(frameNavbarProjets);

        frameTopbarProjets = new QFrame(scrollProjetsContent);
        frameTopbarProjets->setObjectName("frameTopbarProjets");
        frameTopbarProjets->setMinimumSize(QSize(0, 76));
        frameTopbarProjets->setMaximumSize(QSize(16777215, 76));
        topbarProjLayout = new QVBoxLayout(frameTopbarProjets);
        topbarProjLayout->setSpacing(2);
        topbarProjLayout->setObjectName("topbarProjLayout");
        topbarProjLayout->setContentsMargins(32, 14, 32, 14);
        topbarTitleProj = new QLabel(frameTopbarProjets);
        topbarTitleProj->setObjectName("topbarTitleProj");

        topbarProjLayout->addWidget(topbarTitleProj);

        topbarSubProj = new QLabel(frameTopbarProjets);
        topbarSubProj->setObjectName("topbarSubProj");

        topbarProjLayout->addWidget(topbarSubProj);


        projetsContentLayout->addWidget(frameTopbarProjets);

        statsProjLayout = new QHBoxLayout();
        statsProjLayout->setSpacing(16);
        statsProjLayout->setObjectName("statsProjLayout");
        statsProjLayout->setContentsMargins(32, 20, 32, 20);
        cardProjStat1 = new QFrame(scrollProjetsContent);
        cardProjStat1->setObjectName("cardProjStat1");
        cardProjStat1->setMinimumSize(QSize(0, 120));
        cardProjStat1Layout = new QVBoxLayout(cardProjStat1);
        cardProjStat1Layout->setSpacing(4);
        cardProjStat1Layout->setObjectName("cardProjStat1Layout");
        cardProjStat1Layout->setContentsMargins(20, 18, 20, 18);
        cardProjTitle1 = new QLabel(cardProjStat1);
        cardProjTitle1->setObjectName("cardProjTitle1");

        cardProjStat1Layout->addWidget(cardProjTitle1);

        cardProjValue1 = new QLabel(cardProjStat1);
        cardProjValue1->setObjectName("cardProjValue1");

        cardProjStat1Layout->addWidget(cardProjValue1);

        cardProjSub1 = new QLabel(cardProjStat1);
        cardProjSub1->setObjectName("cardProjSub1");

        cardProjStat1Layout->addWidget(cardProjSub1);


        statsProjLayout->addWidget(cardProjStat1);

        cardProjStat2 = new QFrame(scrollProjetsContent);
        cardProjStat2->setObjectName("cardProjStat2");
        cardProjStat2->setMinimumSize(QSize(0, 120));
        cardProjStat2Layout = new QVBoxLayout(cardProjStat2);
        cardProjStat2Layout->setSpacing(4);
        cardProjStat2Layout->setObjectName("cardProjStat2Layout");
        cardProjStat2Layout->setContentsMargins(20, 18, 20, 18);
        cardProjTitle2 = new QLabel(cardProjStat2);
        cardProjTitle2->setObjectName("cardProjTitle2");

        cardProjStat2Layout->addWidget(cardProjTitle2);

        cardProjValue2 = new QLabel(cardProjStat2);
        cardProjValue2->setObjectName("cardProjValue2");

        cardProjStat2Layout->addWidget(cardProjValue2);

        cardProjSub2 = new QLabel(cardProjStat2);
        cardProjSub2->setObjectName("cardProjSub2");

        cardProjStat2Layout->addWidget(cardProjSub2);


        statsProjLayout->addWidget(cardProjStat2);

        cardProjStat3 = new QFrame(scrollProjetsContent);
        cardProjStat3->setObjectName("cardProjStat3");
        cardProjStat3->setMinimumSize(QSize(0, 120));
        cardProjStat3Layout = new QVBoxLayout(cardProjStat3);
        cardProjStat3Layout->setSpacing(4);
        cardProjStat3Layout->setObjectName("cardProjStat3Layout");
        cardProjStat3Layout->setContentsMargins(20, 18, 20, 18);
        cardProjTitle3 = new QLabel(cardProjStat3);
        cardProjTitle3->setObjectName("cardProjTitle3");

        cardProjStat3Layout->addWidget(cardProjTitle3);

        cardProjValue3 = new QLabel(cardProjStat3);
        cardProjValue3->setObjectName("cardProjValue3");

        cardProjStat3Layout->addWidget(cardProjValue3);

        cardProjSub3 = new QLabel(cardProjStat3);
        cardProjSub3->setObjectName("cardProjSub3");

        cardProjStat3Layout->addWidget(cardProjSub3);


        statsProjLayout->addWidget(cardProjStat3);

        cardProjStat4 = new QFrame(scrollProjetsContent);
        cardProjStat4->setObjectName("cardProjStat4");
        cardProjStat4->setMinimumSize(QSize(0, 120));
        cardProjStat4Layout = new QVBoxLayout(cardProjStat4);
        cardProjStat4Layout->setSpacing(4);
        cardProjStat4Layout->setObjectName("cardProjStat4Layout");
        cardProjStat4Layout->setContentsMargins(20, 18, 20, 18);
        cardProjTitle4 = new QLabel(cardProjStat4);
        cardProjTitle4->setObjectName("cardProjTitle4");

        cardProjStat4Layout->addWidget(cardProjTitle4);

        cardProjValue4 = new QLabel(cardProjStat4);
        cardProjValue4->setObjectName("cardProjValue4");

        cardProjStat4Layout->addWidget(cardProjValue4);

        cardProjSub4 = new QLabel(cardProjStat4);
        cardProjSub4->setObjectName("cardProjSub4");

        cardProjStat4Layout->addWidget(cardProjSub4);


        statsProjLayout->addWidget(cardProjStat4);


        projetsContentLayout->addLayout(statsProjLayout);

        cardFormProjets = new QFrame(scrollProjetsContent);
        cardFormProjets->setObjectName("cardFormProjets");
        cardFormProjets->setMinimumSize(QSize(0, 220));
        formProjLayout = new QVBoxLayout(cardFormProjets);
        formProjLayout->setSpacing(14);
        formProjLayout->setObjectName("formProjLayout");
        formProjLayout->setContentsMargins(24, 20, 24, 20);
        formTitleProj = new QLabel(cardFormProjets);
        formTitleProj->setObjectName("formTitleProj");

        formProjLayout->addWidget(formTitleProj);

        formProjGrid = new QGridLayout();
        formProjGrid->setSpacing(12);
        formProjGrid->setObjectName("formProjGrid");
        lblProjID = new QLabel(cardFormProjets);
        lblProjID->setObjectName("lblProjID");

        formProjGrid->addWidget(lblProjID, 0, 0, 1, 1);

        lblProjNom = new QLabel(cardFormProjets);
        lblProjNom->setObjectName("lblProjNom");

        formProjGrid->addWidget(lblProjNom, 0, 1, 1, 1);

        lblProjCat = new QLabel(cardFormProjets);
        lblProjCat->setObjectName("lblProjCat");

        formProjGrid->addWidget(lblProjCat, 0, 2, 1, 1);

        lblProjStatut = new QLabel(cardFormProjets);
        lblProjStatut->setObjectName("lblProjStatut");

        formProjGrid->addWidget(lblProjStatut, 0, 3, 1, 1);

        lblProjEquipe = new QLabel(cardFormProjets);
        lblProjEquipe->setObjectName("lblProjEquipe");

        formProjGrid->addWidget(lblProjEquipe, 0, 4, 1, 1);

        lineEditProjID = new QLineEdit(cardFormProjets);
        lineEditProjID->setObjectName("lineEditProjID");
        lineEditProjID->setReadOnly(true);

        formProjGrid->addWidget(lineEditProjID, 1, 0, 1, 1);

        lineEditProjNom = new QLineEdit(cardFormProjets);
        lineEditProjNom->setObjectName("lineEditProjNom");

        formProjGrid->addWidget(lineEditProjNom, 1, 1, 1, 1);

        comboBoxProjCategorie = new QComboBox(cardFormProjets);
        comboBoxProjCategorie->addItem(QString());
        comboBoxProjCategorie->addItem(QString());
        comboBoxProjCategorie->addItem(QString());
        comboBoxProjCategorie->addItem(QString());
        comboBoxProjCategorie->addItem(QString());
        comboBoxProjCategorie->setObjectName("comboBoxProjCategorie");

        formProjGrid->addWidget(comboBoxProjCategorie, 1, 2, 1, 1);

        comboBoxProjStatut = new QComboBox(cardFormProjets);
        comboBoxProjStatut->addItem(QString());
        comboBoxProjStatut->addItem(QString());
        comboBoxProjStatut->addItem(QString());
        comboBoxProjStatut->setObjectName("comboBoxProjStatut");

        formProjGrid->addWidget(comboBoxProjStatut, 1, 3, 1, 1);

        lineEditProjEquipe = new QLineEdit(cardFormProjets);
        lineEditProjEquipe->setObjectName("lineEditProjEquipe");

        formProjGrid->addWidget(lineEditProjEquipe, 1, 4, 1, 1);


        formProjLayout->addLayout(formProjGrid);

        formProjButtonsLayout = new QHBoxLayout();
        formProjButtonsLayout->setSpacing(12);
        formProjButtonsLayout->setObjectName("formProjButtonsLayout");
        btnProjAjouter = new QPushButton(cardFormProjets);
        btnProjAjouter->setObjectName("btnProjAjouter");
        btnProjAjouter->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        formProjButtonsLayout->addWidget(btnProjAjouter);

        btnProjModifier = new QPushButton(cardFormProjets);
        btnProjModifier->setObjectName("btnProjModifier");
        btnProjModifier->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        formProjButtonsLayout->addWidget(btnProjModifier);

        btnProjSupprimer = new QPushButton(cardFormProjets);
        btnProjSupprimer->setObjectName("btnProjSupprimer");
        btnProjSupprimer->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        formProjButtonsLayout->addWidget(btnProjSupprimer);

        btnProjConsulter = new QPushButton(cardFormProjets);
        btnProjConsulter->setObjectName("btnProjConsulter");
        btnProjConsulter->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        formProjButtonsLayout->addWidget(btnProjConsulter);

        formProjBtnSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        formProjButtonsLayout->addItem(formProjBtnSpacer);


        formProjLayout->addLayout(formProjButtonsLayout);


        projetsContentLayout->addWidget(cardFormProjets);

        searchProjLayout = new QHBoxLayout();
        searchProjLayout->setSpacing(12);
        searchProjLayout->setObjectName("searchProjLayout");
        searchProjLayout->setContentsMargins(32, 0, 32, 20);
        lineEditRechercheProj = new QLineEdit(scrollProjetsContent);
        lineEditRechercheProj->setObjectName("lineEditRechercheProj");
        lineEditRechercheProj->setMinimumSize(QSize(400, 42));

        searchProjLayout->addWidget(lineEditRechercheProj);

        btnProjRechercher = new QPushButton(scrollProjetsContent);
        btnProjRechercher->setObjectName("btnProjRechercher");
        btnProjRechercher->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        searchProjLayout->addWidget(btnProjRechercher);

        btnProjTrier = new QPushButton(scrollProjetsContent);
        btnProjTrier->setObjectName("btnProjTrier");
        btnProjTrier->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        searchProjLayout->addWidget(btnProjTrier);

        searchProjSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        searchProjLayout->addItem(searchProjSpacer);


        projetsContentLayout->addLayout(searchProjLayout);

        cardTableProjets = new QFrame(scrollProjetsContent);
        cardTableProjets->setObjectName("cardTableProjets");
        cardTableProjets->setMinimumSize(QSize(0, 380));
        tableProjLayout = new QVBoxLayout(cardTableProjets);
        tableProjLayout->setSpacing(12);
        tableProjLayout->setObjectName("tableProjLayout");
        tableProjLayout->setContentsMargins(20, 20, 20, 20);
        tableTitleProj = new QLabel(cardTableProjets);
        tableTitleProj->setObjectName("tableTitleProj");

        tableProjLayout->addWidget(tableTitleProj);

        tableWidgetProjets = new QTableWidget(cardTableProjets);
        if (tableWidgetProjets->columnCount() < 6)
            tableWidgetProjets->setColumnCount(6);
        QTableWidgetItem *__qtablewidgetitem32 = new QTableWidgetItem();
        tableWidgetProjets->setHorizontalHeaderItem(0, __qtablewidgetitem32);
        QTableWidgetItem *__qtablewidgetitem33 = new QTableWidgetItem();
        tableWidgetProjets->setHorizontalHeaderItem(1, __qtablewidgetitem33);
        QTableWidgetItem *__qtablewidgetitem34 = new QTableWidgetItem();
        tableWidgetProjets->setHorizontalHeaderItem(2, __qtablewidgetitem34);
        QTableWidgetItem *__qtablewidgetitem35 = new QTableWidgetItem();
        tableWidgetProjets->setHorizontalHeaderItem(3, __qtablewidgetitem35);
        QTableWidgetItem *__qtablewidgetitem36 = new QTableWidgetItem();
        tableWidgetProjets->setHorizontalHeaderItem(4, __qtablewidgetitem36);
        QTableWidgetItem *__qtablewidgetitem37 = new QTableWidgetItem();
        tableWidgetProjets->setHorizontalHeaderItem(5, __qtablewidgetitem37);
        tableWidgetProjets->setObjectName("tableWidgetProjets");
        tableWidgetProjets->setAlternatingRowColors(true);
        tableWidgetProjets->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);

        tableProjLayout->addWidget(tableWidgetProjets);


        projetsContentLayout->addWidget(cardTableProjets);

        scrollProjets->setWidget(scrollProjetsContent);

        projetsOuterLayout->addWidget(scrollProjets);

        stackedWidget->addWidget(pageProjets);

        mainLayout->addWidget(stackedWidget);

        integration->setCentralWidget(centralWidget);

        retranslateUi(integration);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(integration);
    } // setupUi

    void retranslateUi(QMainWindow *integration)
    {
        integration->setWindowTitle(QCoreApplication::translate("integration", "HACKNOVA \342\200\224 Smart Hackathon Management", nullptr));
        labelLoginLogo->setText(QCoreApplication::translate("integration", "HN", nullptr));
        labelLoginBrandTitle->setText(QCoreApplication::translate("integration", "HACKNOVA", nullptr));
        labelLoginBrandSub->setText(QCoreApplication::translate("integration", "SMART HACKATHON MANAGEMENT", nullptr));
        labelLoginBrandSlogan->setText(QCoreApplication::translate("integration", "Plateforme intelligente de gestion de hackathons universitaires.", nullptr));
        labelLoginBrandVersion->setText(QCoreApplication::translate("integration", "VERSION 1.0.0", nullptr));
        labelLoginBrandTeam->setText(QCoreApplication::translate("integration", "GROUPE EL FALLEGA", nullptr));
        labelLoginTitle->setText(QCoreApplication::translate("integration", "Bienvenue", nullptr));
        labelLoginSub->setText(QCoreApplication::translate("integration", "Connectez-vous pour acc\303\251der \303\240 votre espace de gestion.", nullptr));
        labelLoginField->setText(QCoreApplication::translate("integration", "IDENTIFIANT", nullptr));
        lineEditIdentifiant->setPlaceholderText(QCoreApplication::translate("integration", "Entrez votre identifiant", nullptr));
        labelLoginField2->setText(QCoreApplication::translate("integration", "MOT DE PASSE", nullptr));
        lineEditMotDePasse->setPlaceholderText(QCoreApplication::translate("integration", "Entrez votre mot de passe", nullptr));
        checkBoxSouvenir->setText(QCoreApplication::translate("integration", "Se souvenir de moi", nullptr));
        pushButtonConnexion->setText(QCoreApplication::translate("integration", "SE CONNECTER", nullptr));
        pushButtonCGU->setText(QCoreApplication::translate("integration", "Conditions g\303\251n\303\251rales d'utilisation", nullptr));
        pushButtonPolitique->setText(QCoreApplication::translate("integration", "Politique d'utilisation", nullptr));
        pushButtonAPropos->setText(QCoreApplication::translate("integration", "\303\200 propos de HACKNOVA", nullptr));
        labelLoginFooter->setText(QCoreApplication::translate("integration", "\302\251 2025 HACKNOVA \342\200\224 Groupe EL FALLEGA \342\200\224 Tous droits r\303\251serv\303\251s", nullptr));
        labelNavLogo->setText(QCoreApplication::translate("integration", "HN", nullptr));
        labelNavBrand->setText(QCoreApplication::translate("integration", "HACKNOVA", nullptr));
        labelNavSub->setText(QCoreApplication::translate("integration", "SMART HACKATHON", nullptr));
        navDashboardDashboard->setText(QCoreApplication::translate("integration", "DASHBOARD", nullptr));
        navEmployesDashboard->setText(QCoreApplication::translate("integration", "EMPLOYES", nullptr));
        navSallesDashboard->setText(QCoreApplication::translate("integration", "SALLES", nullptr));
        navEvaluateursDashboard->setText(QCoreApplication::translate("integration", "EVALUATEURS", nullptr));
        navParticipantsDashboard->setText(QCoreApplication::translate("integration", "PARTICIPANTS", nullptr));
        navSponsorsDashboard->setText(QCoreApplication::translate("integration", "SPONSORS", nullptr));
        navProjetsDashboard->setText(QCoreApplication::translate("integration", "PROJETS", nullptr));
        navDeconnexionDashboard->setText(QCoreApplication::translate("integration", "DECONNEXION", nullptr));
        labelTopbarTitle->setText(QCoreApplication::translate("integration", "Dashboard", nullptr));
        labelTopbarSub->setText(QCoreApplication::translate("integration", "Vue globale de votre Smart Hackathon Management", nullptr));
        navNotifDashboard->setText(QCoreApplication::translate("integration", "NOTIFICATIONS", nullptr));
        navProfileDashboard->setText(QCoreApplication::translate("integration", "PROFIL", nullptr));
        labelTopbarUserName->setText(QCoreApplication::translate("integration", "Utilisateur", nullptr));
        labelTopbarUserRole->setText(QCoreApplication::translate("integration", "Administrateur", nullptr));
        labelTopbarAvatar->setText(QCoreApplication::translate("integration", "US", nullptr));
        cardStatTitle->setText(QCoreApplication::translate("integration", "PARTICIPANTS", nullptr));
        cardStatValue->setText(QCoreApplication::translate("integration", "0", nullptr));
        cardStatSub->setText(QCoreApplication::translate("integration", "Total enregistr\303\251", nullptr));
        cardStatTitle2->setText(QCoreApplication::translate("integration", "PROJETS", nullptr));
        cardStatValue2->setText(QCoreApplication::translate("integration", "0", nullptr));
        cardStatSub2->setText(QCoreApplication::translate("integration", "Total projets", nullptr));
        cardStatTitle3->setText(QCoreApplication::translate("integration", "SALLES", nullptr));
        cardStatValue3->setText(QCoreApplication::translate("integration", "0", nullptr));
        cardStatSub3->setText(QCoreApplication::translate("integration", "Total salles", nullptr));
        cardStatTitle4->setText(QCoreApplication::translate("integration", "SPONSORS", nullptr));
        cardStatValue4->setText(QCoreApplication::translate("integration", "0", nullptr));
        cardStatSub4->setText(QCoreApplication::translate("integration", "Total sponsors", nullptr));
        labelDonutTitle->setText(QCoreApplication::translate("integration", "R\303\251partition des projets", nullptr));
        labelDonutSub->setText(QCoreApplication::translate("integration", "Par cat\303\251gorie", nullptr));
        chartDonutCenterValue->setText(QCoreApplication::translate("integration", "0", nullptr));
        chartDonutCenterLabel->setText(QCoreApplication::translate("integration", "TOTAL", nullptr));
        labelDonutFooter->setText(QCoreApplication::translate("integration", "Mise \303\240 jour en temps r\303\251el", nullptr));
        labelBarsHTitle->setText(QCoreApplication::translate("integration", "Projets par statut", nullptr));
        labelBarsHSub->setText(QCoreApplication::translate("integration", "R\303\251partition actuelle", nullptr));
        barLabel1->setText(QCoreApplication::translate("integration", "Termin\303\251s", nullptr));
        barValue1->setText(QCoreApplication::translate("integration", "0%", nullptr));
        barLabel2->setText(QCoreApplication::translate("integration", "En cours", nullptr));
        barValue2->setText(QCoreApplication::translate("integration", "0%", nullptr));
        barLabel3->setText(QCoreApplication::translate("integration", "En attente", nullptr));
        barValue3->setText(QCoreApplication::translate("integration", "0%", nullptr));
        barLabel4->setText(QCoreApplication::translate("integration", "Rejet\303\251s", nullptr));
        barValue4->setText(QCoreApplication::translate("integration", "0%", nullptr));
        labelProgressTitle->setText(QCoreApplication::translate("integration", "PROGRESSION GLOBALE DU HACKATHON", nullptr));
        labelProgressNote->setText(QCoreApplication::translate("integration", "Phase 1/5 \342\200\224 Pr\303\251paration", nullptr));
        labelBarsVTitle->setText(QCoreApplication::translate("integration", "\303\211volution des participants", nullptr));
        labelBarsVSub->setText(QCoreApplication::translate("integration", "Par \303\251quipe", nullptr));
        barVValue1->setText(QCoreApplication::translate("integration", "0", nullptr));
        barVLabel1->setText(QCoreApplication::translate("integration", "EQ1", nullptr));
        barVValue2->setText(QCoreApplication::translate("integration", "0", nullptr));
        barVLabel2->setText(QCoreApplication::translate("integration", "EQ2", nullptr));
        barVValue3->setText(QCoreApplication::translate("integration", "0", nullptr));
        barVLabel3->setText(QCoreApplication::translate("integration", "EQ3", nullptr));
        barVValue4->setText(QCoreApplication::translate("integration", "0", nullptr));
        barVLabel4->setText(QCoreApplication::translate("integration", "EQ4", nullptr));
        barVValue5->setText(QCoreApplication::translate("integration", "0", nullptr));
        barVLabel5->setText(QCoreApplication::translate("integration", "EQ5", nullptr));
        barVValue6->setText(QCoreApplication::translate("integration", "0", nullptr));
        barVLabel6->setText(QCoreApplication::translate("integration", "EQ6", nullptr));
        labelBarsVFooterLeft->setText(QCoreApplication::translate("integration", "TOTAL : 0 inscriptions", nullptr));
        labelBarsVFooterRight->setText(QCoreApplication::translate("integration", "0% vs. p\303\251riode pr\303\251c\303\251dente", nullptr));
        chatTitle->setText(QCoreApplication::translate("integration", "HACKNOVA AI ASSISTANT", nullptr));
        chatStatusOnline->setText(QCoreApplication::translate("integration", "\342\227\217 Online", nullptr));
        chatSub->setText(QCoreApplication::translate("integration", "Intelligent Assistant \342\200\224 Posez vos questions sur la plateforme", nullptr));
        chatQuickTitle->setText(QCoreApplication::translate("integration", "RACCOURCIS RAPIDES", nullptr));
        chatQuick1->setText(QCoreApplication::translate("integration", "Donne-moi les statistiques", nullptr));
        chatQuick2->setText(QCoreApplication::translate("integration", "\303\211tat des projets", nullptr));
        chatQuick3->setText(QCoreApplication::translate("integration", "Liste des sponsors", nullptr));
        chatQuick4->setText(QCoreApplication::translate("integration", "Aide / Commandes", nullptr));
        chatInput->setPlaceholderText(QCoreApplication::translate("integration", "\303\211crire un message...", nullptr));
        chatSendBtn->setText(QCoreApplication::translate("integration", "ENVOYER", nullptr));
        labelNavLogoEmp->setText(QCoreApplication::translate("integration", "HN", nullptr));
        labelNavBrandEmp->setText(QCoreApplication::translate("integration", "HACKNOVA", nullptr));
        labelNavSubEmp->setText(QCoreApplication::translate("integration", "SMART HACKATHON", nullptr));
        navDashboardEmployes->setText(QCoreApplication::translate("integration", "DASHBOARD", nullptr));
        navEmployesEmployes->setText(QCoreApplication::translate("integration", "EMPLOYES", nullptr));
        navSallesEmployes->setText(QCoreApplication::translate("integration", "SALLES", nullptr));
        navEvaluateursEmployes->setText(QCoreApplication::translate("integration", "EVALUATEURS", nullptr));
        navParticipantsEmployes->setText(QCoreApplication::translate("integration", "PARTICIPANTS", nullptr));
        navSponsorsEmployes->setText(QCoreApplication::translate("integration", "SPONSORS", nullptr));
        navProjetsEmployes->setText(QCoreApplication::translate("integration", "PROJETS", nullptr));
        navDeconnexionEmployes->setText(QCoreApplication::translate("integration", "DECONNEXION", nullptr));
        topbarTitleEmp->setText(QCoreApplication::translate("integration", "Gestion des employ\303\251s", nullptr));
        topbarSubEmp->setText(QCoreApplication::translate("integration", "G\303\251rez les comptes, r\303\264les et privil\303\250ges des employ\303\251s", nullptr));
        cardEmpTitle1->setText(QCoreApplication::translate("integration", "TOTAL EMPLOYES", nullptr));
        cardEmpValue1->setText(QCoreApplication::translate("integration", "0", nullptr));
        cardEmpSub1->setText(QCoreApplication::translate("integration", "Employ\303\251s enregistr\303\251s", nullptr));
        cardEmpTitle2->setText(QCoreApplication::translate("integration", "ACTIFS", nullptr));
        cardEmpValue2->setText(QCoreApplication::translate("integration", "0", nullptr));
        cardEmpSub2->setText(QCoreApplication::translate("integration", "Comptes actifs", nullptr));
        cardEmpTitle3->setText(QCoreApplication::translate("integration", "ADMINISTRATEURS", nullptr));
        cardEmpValue3->setText(QCoreApplication::translate("integration", "0", nullptr));
        cardEmpSub3->setText(QCoreApplication::translate("integration", "Acc\303\250s complet", nullptr));
        cardEmpTitle4->setText(QCoreApplication::translate("integration", "INACTIFS", nullptr));
        cardEmpValue4->setText(QCoreApplication::translate("integration", "0", nullptr));
        cardEmpSub4->setText(QCoreApplication::translate("integration", "Comptes d\303\251sactiv\303\251s", nullptr));
        formTitleEmp->setText(QCoreApplication::translate("integration", "Ajouter / Modifier un employ\303\251", nullptr));
        lblEmpID->setText(QCoreApplication::translate("integration", "ID", nullptr));
        lblEmpNom->setText(QCoreApplication::translate("integration", "NOM", nullptr));
        lblEmpPrenom->setText(QCoreApplication::translate("integration", "PRENOM", nullptr));
        lblEmpMdp->setText(QCoreApplication::translate("integration", "MOT DE PASSE", nullptr));
        lblEmpRole->setText(QCoreApplication::translate("integration", "ROLE", nullptr));
        lblEmpStatut->setText(QCoreApplication::translate("integration", "STATUT", nullptr));
        lineEditEmpID->setPlaceholderText(QCoreApplication::translate("integration", "Auto", nullptr));
        lineEditEmpNom->setPlaceholderText(QCoreApplication::translate("integration", "Nom", nullptr));
        lineEditEmpPrenom->setPlaceholderText(QCoreApplication::translate("integration", "Pr\303\251nom", nullptr));
        lineEditEmpMdp->setPlaceholderText(QCoreApplication::translate("integration", "\342\200\242\342\200\242\342\200\242\342\200\242\342\200\242\342\200\242\342\200\242\342\200\242", nullptr));
        comboBoxEmpRole->setItemText(0, QCoreApplication::translate("integration", "Administrateur", nullptr));
        comboBoxEmpRole->setItemText(1, QCoreApplication::translate("integration", "Responsable RH", nullptr));
        comboBoxEmpRole->setItemText(2, QCoreApplication::translate("integration", "Organisateur", nullptr));

        comboBoxEmpStatut->setItemText(0, QCoreApplication::translate("integration", "Actif", nullptr));
        comboBoxEmpStatut->setItemText(1, QCoreApplication::translate("integration", "Inactif", nullptr));

        btnEmpAjouter->setText(QCoreApplication::translate("integration", "AJOUTER", nullptr));
        btnEmpModifier->setText(QCoreApplication::translate("integration", "MODIFIER", nullptr));
        btnEmpSupprimer->setText(QCoreApplication::translate("integration", "SUPPRIMER", nullptr));
        btnEmpConsulter->setText(QCoreApplication::translate("integration", "CONSULTER", nullptr));
        lineEditRechercheEmployes->setPlaceholderText(QCoreApplication::translate("integration", "Rechercher un employ\303\251...", nullptr));
        btnEmpRechercher->setText(QCoreApplication::translate("integration", "RECHERCHER", nullptr));
        btnEmpTrier->setText(QCoreApplication::translate("integration", "TRIER", nullptr));
        tableTitleEmp->setText(QCoreApplication::translate("integration", "Liste des employ\303\251s", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetEmployes->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("integration", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetEmployes->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("integration", "NOM", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidgetEmployes->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("integration", "PRENOM", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidgetEmployes->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("integration", "ROLE", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidgetEmployes->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("integration", "STATUT", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidgetEmployes->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("integration", "ACTIONS", nullptr));
        labelNavLogoSalles->setText(QCoreApplication::translate("integration", "HN", nullptr));
        labelNavBrandSalles->setText(QCoreApplication::translate("integration", "HACKNOVA", nullptr));
        labelNavSubSalles->setText(QCoreApplication::translate("integration", "SMART HACKATHON", nullptr));
        navDashboardSalles->setText(QCoreApplication::translate("integration", "DASHBOARD", nullptr));
        navEmployesSalles->setText(QCoreApplication::translate("integration", "EMPLOYES", nullptr));
        navSallesSalles->setText(QCoreApplication::translate("integration", "SALLES", nullptr));
        navEvaluateursSalles->setText(QCoreApplication::translate("integration", "EVALUATEURS", nullptr));
        navParticipantsSalles->setText(QCoreApplication::translate("integration", "PARTICIPANTS", nullptr));
        navSponsorsSalles->setText(QCoreApplication::translate("integration", "SPONSORS", nullptr));
        navProjetsSalles->setText(QCoreApplication::translate("integration", "PROJETS", nullptr));
        navDeconnexionSalles->setText(QCoreApplication::translate("integration", "DECONNEXION", nullptr));
        topbarTitleSalles->setText(QCoreApplication::translate("integration", "Gestion des salles", nullptr));
        topbarSubSalles->setText(QCoreApplication::translate("integration", "Planifiez et optimisez les espaces du hackathon", nullptr));
        cardSalleTitle1->setText(QCoreApplication::translate("integration", "TOTAL SALLES", nullptr));
        cardSalleValue1->setText(QCoreApplication::translate("integration", "0", nullptr));
        cardSalleSub1->setText(QCoreApplication::translate("integration", "Salles enregistr\303\251es", nullptr));
        cardSalleTitle2->setText(QCoreApplication::translate("integration", "DISPONIBLES", nullptr));
        cardSalleValue2->setText(QCoreApplication::translate("integration", "0", nullptr));
        cardSalleSub2->setText(QCoreApplication::translate("integration", "Pr\303\252tes \303\240 l'emploi", nullptr));
        cardSalleTitle3->setText(QCoreApplication::translate("integration", "OCCUPEES", nullptr));
        cardSalleValue3->setText(QCoreApplication::translate("integration", "0", nullptr));
        cardSalleSub3->setText(QCoreApplication::translate("integration", "En cours d'utilisation", nullptr));
        cardSalleTitle4->setText(QCoreApplication::translate("integration", "CAPACITE TOTALE", nullptr));
        cardSalleValue4->setText(QCoreApplication::translate("integration", "0", nullptr));
        cardSalleSub4->setText(QCoreApplication::translate("integration", "Places disponibles", nullptr));
        formTitleSalles->setText(QCoreApplication::translate("integration", "Ajouter / Modifier une salle", nullptr));
        lblSalleID->setText(QCoreApplication::translate("integration", "ID", nullptr));
        lblSalleNom->setText(QCoreApplication::translate("integration", "NOM", nullptr));
        lblSalleCap->setText(QCoreApplication::translate("integration", "CAPACITE", nullptr));
        lblSalleType->setText(QCoreApplication::translate("integration", "TYPE", nullptr));
        lblSalleDispo->setText(QCoreApplication::translate("integration", "DISPONIBILITE", nullptr));
        lineEditSalleID->setPlaceholderText(QCoreApplication::translate("integration", "Auto", nullptr));
        lineEditSalleNom->setPlaceholderText(QCoreApplication::translate("integration", "Nom de la salle", nullptr));
        comboBoxSalleType->setItemText(0, QCoreApplication::translate("integration", "R\303\251union", nullptr));
        comboBoxSalleType->setItemText(1, QCoreApplication::translate("integration", "Conf\303\251rence", nullptr));
        comboBoxSalleType->setItemText(2, QCoreApplication::translate("integration", "Atelier", nullptr));
        comboBoxSalleType->setItemText(3, QCoreApplication::translate("integration", "Autre", nullptr));

        comboBoxSalleDispo->setItemText(0, QCoreApplication::translate("integration", "Disponible", nullptr));
        comboBoxSalleDispo->setItemText(1, QCoreApplication::translate("integration", "Occup\303\251e", nullptr));
        comboBoxSalleDispo->setItemText(2, QCoreApplication::translate("integration", "Maintenance", nullptr));

        btnSalleAjouter->setText(QCoreApplication::translate("integration", "AJOUTER", nullptr));
        btnSalleModifier->setText(QCoreApplication::translate("integration", "MODIFIER", nullptr));
        btnSalleSupprimer->setText(QCoreApplication::translate("integration", "SUPPRIMER", nullptr));
        btnSalleConsulter->setText(QCoreApplication::translate("integration", "CONSULTER", nullptr));
        lineEditRechercheSalle->setPlaceholderText(QCoreApplication::translate("integration", "Rechercher une salle...", nullptr));
        btnSalleRechercher->setText(QCoreApplication::translate("integration", "RECHERCHER", nullptr));
        btnSalleTrier->setText(QCoreApplication::translate("integration", "TRIER", nullptr));
        tableTitleSalles->setText(QCoreApplication::translate("integration", "Liste des salles", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidgetSalles->horizontalHeaderItem(0);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("integration", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidgetSalles->horizontalHeaderItem(1);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("integration", "NOM", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = tableWidgetSalles->horizontalHeaderItem(2);
        ___qtablewidgetitem8->setText(QCoreApplication::translate("integration", "CAPACITE", nullptr));
        QTableWidgetItem *___qtablewidgetitem9 = tableWidgetSalles->horizontalHeaderItem(3);
        ___qtablewidgetitem9->setText(QCoreApplication::translate("integration", "TYPE", nullptr));
        QTableWidgetItem *___qtablewidgetitem10 = tableWidgetSalles->horizontalHeaderItem(4);
        ___qtablewidgetitem10->setText(QCoreApplication::translate("integration", "DISPONIBILITE", nullptr));
        QTableWidgetItem *___qtablewidgetitem11 = tableWidgetSalles->horizontalHeaderItem(5);
        ___qtablewidgetitem11->setText(QCoreApplication::translate("integration", "ACTIONS", nullptr));
        sbLogoEval->setText(QCoreApplication::translate("integration", "HN", nullptr));
        sbBrandEval->setText(QCoreApplication::translate("integration", "HACKNOVA", nullptr));
        sbSubEval->setText(QCoreApplication::translate("integration", "SMART HACKATHON", nullptr));
        navDashboardEvaluateurs->setText(QCoreApplication::translate("integration", "DASHBOARD", nullptr));
        navEmployesEvaluateurs->setText(QCoreApplication::translate("integration", "EMPLOYES", nullptr));
        navSallesEvaluateurs->setText(QCoreApplication::translate("integration", "SALLES", nullptr));
        navEvaluateursEvaluateurs->setText(QCoreApplication::translate("integration", "EVALUATEURS", nullptr));
        navParticipantsEvaluateurs->setText(QCoreApplication::translate("integration", "PARTICIPANTS", nullptr));
        navSponsorsEvaluateurs->setText(QCoreApplication::translate("integration", "SPONSORS", nullptr));
        navProjetsEvaluateurs->setText(QCoreApplication::translate("integration", "PROJETS", nullptr));
        navDeconnexionEvaluateurs->setText(QCoreApplication::translate("integration", "DECONNEXION", nullptr));
        topbarTitleEval->setText(QCoreApplication::translate("integration", "Gestion des \303\251valuateurs", nullptr));
        topbarSubEval->setText(QCoreApplication::translate("integration", "G\303\251rez les membres du jury et leurs \303\251valuations", nullptr));
        cardEvalTitle1->setText(QCoreApplication::translate("integration", "TOTAL EVALUATEURS", nullptr));
        cardEvalValue1->setText(QCoreApplication::translate("integration", "0", nullptr));
        cardEvalSub1->setText(QCoreApplication::translate("integration", "Membres du jury", nullptr));
        cardEvalTitle2->setText(QCoreApplication::translate("integration", "ACTIFS", nullptr));
        cardEvalValue2->setText(QCoreApplication::translate("integration", "0", nullptr));
        cardEvalSub2->setText(QCoreApplication::translate("integration", "Disponibles pour \303\251valuer", nullptr));
        cardEvalTitle3->setText(QCoreApplication::translate("integration", "INACTIFS", nullptr));
        cardEvalValue3->setText(QCoreApplication::translate("integration", "0", nullptr));
        cardEvalSub3->setText(QCoreApplication::translate("integration", "Non disponibles", nullptr));
        formTitleEval->setText(QCoreApplication::translate("integration", "Ajouter / Modifier un \303\251valuateur", nullptr));
        lblEvalID->setText(QCoreApplication::translate("integration", "ID", nullptr));
        lblEvalNom->setText(QCoreApplication::translate("integration", "NOM", nullptr));
        lblEvalPrenom->setText(QCoreApplication::translate("integration", "PRENOM", nullptr));
        lblEvalEmail->setText(QCoreApplication::translate("integration", "EMAIL", nullptr));
        lblEvalStatut->setText(QCoreApplication::translate("integration", "STATUT", nullptr));
        lineEditEvalID->setPlaceholderText(QCoreApplication::translate("integration", "Auto", nullptr));
        lineEditEvalNom->setPlaceholderText(QCoreApplication::translate("integration", "Nom", nullptr));
        lineEditEvalPrenom->setPlaceholderText(QCoreApplication::translate("integration", "Pr\303\251nom", nullptr));
        lineEditEvalEmail->setPlaceholderText(QCoreApplication::translate("integration", "email@exemple.com", nullptr));
        comboBoxEvalStatut->setItemText(0, QCoreApplication::translate("integration", "Actif", nullptr));
        comboBoxEvalStatut->setItemText(1, QCoreApplication::translate("integration", "Inactif", nullptr));

        btnEvalAjouter->setText(QCoreApplication::translate("integration", "AJOUTER", nullptr));
        btnEvalModifier->setText(QCoreApplication::translate("integration", "MODIFIER", nullptr));
        btnEvalSupprimer->setText(QCoreApplication::translate("integration", "SUPPRIMER", nullptr));
        btnEvalConsulter->setText(QCoreApplication::translate("integration", "CONSULTER", nullptr));
        lineEditRechercheEval->setPlaceholderText(QCoreApplication::translate("integration", "Rechercher un \303\251valuateur...", nullptr));
        btnEvalRechercher->setText(QCoreApplication::translate("integration", "RECHERCHER", nullptr));
        btnEvalTrier->setText(QCoreApplication::translate("integration", "TRIER", nullptr));
        tableTitleEval->setText(QCoreApplication::translate("integration", "Liste des \303\251valuateurs", nullptr));
        QTableWidgetItem *___qtablewidgetitem12 = tableWidgetEvaluateurs->horizontalHeaderItem(0);
        ___qtablewidgetitem12->setText(QCoreApplication::translate("integration", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem13 = tableWidgetEvaluateurs->horizontalHeaderItem(1);
        ___qtablewidgetitem13->setText(QCoreApplication::translate("integration", "NOM", nullptr));
        QTableWidgetItem *___qtablewidgetitem14 = tableWidgetEvaluateurs->horizontalHeaderItem(2);
        ___qtablewidgetitem14->setText(QCoreApplication::translate("integration", "PRENOM", nullptr));
        QTableWidgetItem *___qtablewidgetitem15 = tableWidgetEvaluateurs->horizontalHeaderItem(3);
        ___qtablewidgetitem15->setText(QCoreApplication::translate("integration", "EMAIL", nullptr));
        QTableWidgetItem *___qtablewidgetitem16 = tableWidgetEvaluateurs->horizontalHeaderItem(4);
        ___qtablewidgetitem16->setText(QCoreApplication::translate("integration", "STATUT", nullptr));
        QTableWidgetItem *___qtablewidgetitem17 = tableWidgetEvaluateurs->horizontalHeaderItem(5);
        ___qtablewidgetitem17->setText(QCoreApplication::translate("integration", "ACTIONS", nullptr));
        sbLogoPart->setText(QCoreApplication::translate("integration", "HN", nullptr));
        sbBrandPart->setText(QCoreApplication::translate("integration", "HACKNOVA", nullptr));
        sbSubPart->setText(QCoreApplication::translate("integration", "SMART HACKATHON", nullptr));
        navDashboardParticipants->setText(QCoreApplication::translate("integration", "DASHBOARD", nullptr));
        navEmployesParticipants->setText(QCoreApplication::translate("integration", "EMPLOYES", nullptr));
        navSallesParticipants->setText(QCoreApplication::translate("integration", "SALLES", nullptr));
        navEvaluateursParticipants->setText(QCoreApplication::translate("integration", "EVALUATEURS", nullptr));
        navParticipantsParticipants->setText(QCoreApplication::translate("integration", "PARTICIPANTS", nullptr));
        navSponsorsParticipants->setText(QCoreApplication::translate("integration", "SPONSORS", nullptr));
        navProjetsParticipants->setText(QCoreApplication::translate("integration", "PROJETS", nullptr));
        navDeconnexionParticipants->setText(QCoreApplication::translate("integration", "DECONNEXION", nullptr));
        topbarTitlePart->setText(QCoreApplication::translate("integration", "Gestion des participants", nullptr));
        topbarSubPart->setText(QCoreApplication::translate("integration", "G\303\251rez les inscriptions et les \303\251quipes des participants", nullptr));
        cardPartTitle1->setText(QCoreApplication::translate("integration", "TOTAL PARTICIPANTS", nullptr));
        cardPartValue1->setText(QCoreApplication::translate("integration", "0", nullptr));
        cardPartSub1->setText(QCoreApplication::translate("integration", "Inscrits au hackathon", nullptr));
        cardPartTitle2->setText(QCoreApplication::translate("integration", "PARTICIPANTS AVEC CV", nullptr));
        cardPartValue2->setText(QCoreApplication::translate("integration", "0", nullptr));
        cardPartSub2->setText(QCoreApplication::translate("integration", "CV trait\303\251s", nullptr));
        cardPartTitle3->setText(QCoreApplication::translate("integration", "AFFECTES A UNE EQUIPE", nullptr));
        cardPartValue3->setText(QCoreApplication::translate("integration", "0", nullptr));
        cardPartSub3->setText(QCoreApplication::translate("integration", "R\303\251partis en \303\251quipes", nullptr));
        formTitlePart->setText(QCoreApplication::translate("integration", "Ajouter / Modifier un participant", nullptr));
        lblPartID->setText(QCoreApplication::translate("integration", "ID", nullptr));
        lblPartNom->setText(QCoreApplication::translate("integration", "NOM", nullptr));
        lblPartPrenom->setText(QCoreApplication::translate("integration", "PRENOM", nullptr));
        lblPartEmail->setText(QCoreApplication::translate("integration", "EMAIL", nullptr));
        lblPartTel->setText(QCoreApplication::translate("integration", "TELEPHONE", nullptr));
        lblPartEquipe->setText(QCoreApplication::translate("integration", "EQUIPE", nullptr));
        lineEditPartID->setPlaceholderText(QCoreApplication::translate("integration", "Auto", nullptr));
        lineEditPartNom->setPlaceholderText(QCoreApplication::translate("integration", "Nom", nullptr));
        lineEditPartPrenom->setPlaceholderText(QCoreApplication::translate("integration", "Pr\303\251nom", nullptr));
        lineEditPartEmail->setPlaceholderText(QCoreApplication::translate("integration", "email@exemple.com", nullptr));
        lineEditPartTel->setPlaceholderText(QCoreApplication::translate("integration", "+216 XX XXX XXX", nullptr));
        lineEditPartEquipe->setPlaceholderText(QCoreApplication::translate("integration", "\303\211quipe", nullptr));
        btnPartAjouter->setText(QCoreApplication::translate("integration", "AJOUTER", nullptr));
        btnPartModifier->setText(QCoreApplication::translate("integration", "MODIFIER", nullptr));
        btnPartSupprimer->setText(QCoreApplication::translate("integration", "SUPPRIMER", nullptr));
        btnPartConsulter->setText(QCoreApplication::translate("integration", "CONSULTER", nullptr));
        lineEditRecherchePart->setPlaceholderText(QCoreApplication::translate("integration", "Rechercher un participant...", nullptr));
        btnPartRechercher->setText(QCoreApplication::translate("integration", "RECHERCHER", nullptr));
        btnPartTrier->setText(QCoreApplication::translate("integration", "TRIER", nullptr));
        tableTitlePart->setText(QCoreApplication::translate("integration", "Liste des participants", nullptr));
        QTableWidgetItem *___qtablewidgetitem18 = tableWidgetParticipants->horizontalHeaderItem(0);
        ___qtablewidgetitem18->setText(QCoreApplication::translate("integration", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem19 = tableWidgetParticipants->horizontalHeaderItem(1);
        ___qtablewidgetitem19->setText(QCoreApplication::translate("integration", "NOM", nullptr));
        QTableWidgetItem *___qtablewidgetitem20 = tableWidgetParticipants->horizontalHeaderItem(2);
        ___qtablewidgetitem20->setText(QCoreApplication::translate("integration", "PRENOM", nullptr));
        QTableWidgetItem *___qtablewidgetitem21 = tableWidgetParticipants->horizontalHeaderItem(3);
        ___qtablewidgetitem21->setText(QCoreApplication::translate("integration", "EMAIL", nullptr));
        QTableWidgetItem *___qtablewidgetitem22 = tableWidgetParticipants->horizontalHeaderItem(4);
        ___qtablewidgetitem22->setText(QCoreApplication::translate("integration", "TELEPHONE", nullptr));
        QTableWidgetItem *___qtablewidgetitem23 = tableWidgetParticipants->horizontalHeaderItem(5);
        ___qtablewidgetitem23->setText(QCoreApplication::translate("integration", "CV", nullptr));
        QTableWidgetItem *___qtablewidgetitem24 = tableWidgetParticipants->horizontalHeaderItem(6);
        ___qtablewidgetitem24->setText(QCoreApplication::translate("integration", "EQUIPE", nullptr));
        QTableWidgetItem *___qtablewidgetitem25 = tableWidgetParticipants->horizontalHeaderItem(7);
        ___qtablewidgetitem25->setText(QCoreApplication::translate("integration", "ACTIONS", nullptr));
        sbLogoSpon->setText(QCoreApplication::translate("integration", "HN", nullptr));
        sbBrandSpon->setText(QCoreApplication::translate("integration", "HACKNOVA", nullptr));
        sbSubSpon->setText(QCoreApplication::translate("integration", "SMART HACKATHON", nullptr));
        navDashboardSponsors->setText(QCoreApplication::translate("integration", "DASHBOARD", nullptr));
        navEmployesSponsors->setText(QCoreApplication::translate("integration", "EMPLOYES", nullptr));
        navSallesSponsors->setText(QCoreApplication::translate("integration", "SALLES", nullptr));
        navEvaluateursSponsors->setText(QCoreApplication::translate("integration", "EVALUATEURS", nullptr));
        navParticipantsSponsors->setText(QCoreApplication::translate("integration", "PARTICIPANTS", nullptr));
        navSponsorsSponsors->setText(QCoreApplication::translate("integration", "SPONSORS", nullptr));
        navProjetsSponsors->setText(QCoreApplication::translate("integration", "PROJETS", nullptr));
        navDeconnexionSponsors->setText(QCoreApplication::translate("integration", "DECONNEXION", nullptr));
        topbarTitleSpon->setText(QCoreApplication::translate("integration", "Gestion des sponsors", nullptr));
        topbarSubSpon->setText(QCoreApplication::translate("integration", "G\303\251rez les partenaires et sponsors du hackathon", nullptr));
        cardSponTitle1->setText(QCoreApplication::translate("integration", "TOTAL SPONSORS", nullptr));
        cardSponValue1->setText(QCoreApplication::translate("integration", "0", nullptr));
        cardSponSub1->setText(QCoreApplication::translate("integration", "Partenaires enregistr\303\251s", nullptr));
        cardSponTitle2->setText(QCoreApplication::translate("integration", "ACTIFS", nullptr));
        cardSponValue2->setText(QCoreApplication::translate("integration", "0", nullptr));
        cardSponSub2->setText(QCoreApplication::translate("integration", "Partenariats actifs", nullptr));
        cardSponTitle3->setText(QCoreApplication::translate("integration", "INACTIFS", nullptr));
        cardSponValue3->setText(QCoreApplication::translate("integration", "0", nullptr));
        cardSponSub3->setText(QCoreApplication::translate("integration", "Partenariats inactifs", nullptr));
        formTitleSpon->setText(QCoreApplication::translate("integration", "Ajouter / Modifier un sponsor", nullptr));
        lblSponID->setText(QCoreApplication::translate("integration", "ID", nullptr));
        lblSponEntreprise->setText(QCoreApplication::translate("integration", "ENTREPRISE", nullptr));
        lblSponContact->setText(QCoreApplication::translate("integration", "CONTACT", nullptr));
        lblSponType->setText(QCoreApplication::translate("integration", "TYPE", nullptr));
        lblSponStatut->setText(QCoreApplication::translate("integration", "STATUT", nullptr));
        lineEditSponID->setPlaceholderText(QCoreApplication::translate("integration", "Auto", nullptr));
        lineEditSponEntreprise->setPlaceholderText(QCoreApplication::translate("integration", "Nom entreprise", nullptr));
        lineEditSponContact->setPlaceholderText(QCoreApplication::translate("integration", "Nom du contact", nullptr));
        comboBoxSponType->setItemText(0, QCoreApplication::translate("integration", "Gold", nullptr));
        comboBoxSponType->setItemText(1, QCoreApplication::translate("integration", "Silver", nullptr));
        comboBoxSponType->setItemText(2, QCoreApplication::translate("integration", "Bronze", nullptr));

        comboBoxSponStatut->setItemText(0, QCoreApplication::translate("integration", "Actif", nullptr));
        comboBoxSponStatut->setItemText(1, QCoreApplication::translate("integration", "Inactif", nullptr));

        btnSponAjouter->setText(QCoreApplication::translate("integration", "AJOUTER", nullptr));
        btnSponModifier->setText(QCoreApplication::translate("integration", "MODIFIER", nullptr));
        btnSponSupprimer->setText(QCoreApplication::translate("integration", "SUPPRIMER", nullptr));
        btnSponConsulter->setText(QCoreApplication::translate("integration", "CONSULTER", nullptr));
        lineEditRechercheSpon->setPlaceholderText(QCoreApplication::translate("integration", "Rechercher par nom d'entreprise...", nullptr));
        btnSponRechercher->setText(QCoreApplication::translate("integration", "RECHERCHER", nullptr));
        btnSponTrier->setText(QCoreApplication::translate("integration", "TRIER", nullptr));
        tableTitleSpon->setText(QCoreApplication::translate("integration", "Liste des sponsors", nullptr));
        QTableWidgetItem *___qtablewidgetitem26 = tableWidgetSponsors->horizontalHeaderItem(0);
        ___qtablewidgetitem26->setText(QCoreApplication::translate("integration", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem27 = tableWidgetSponsors->horizontalHeaderItem(1);
        ___qtablewidgetitem27->setText(QCoreApplication::translate("integration", "ENTREPRISE", nullptr));
        QTableWidgetItem *___qtablewidgetitem28 = tableWidgetSponsors->horizontalHeaderItem(2);
        ___qtablewidgetitem28->setText(QCoreApplication::translate("integration", "CONTACT", nullptr));
        QTableWidgetItem *___qtablewidgetitem29 = tableWidgetSponsors->horizontalHeaderItem(3);
        ___qtablewidgetitem29->setText(QCoreApplication::translate("integration", "TYPE", nullptr));
        QTableWidgetItem *___qtablewidgetitem30 = tableWidgetSponsors->horizontalHeaderItem(4);
        ___qtablewidgetitem30->setText(QCoreApplication::translate("integration", "STATUT", nullptr));
        QTableWidgetItem *___qtablewidgetitem31 = tableWidgetSponsors->horizontalHeaderItem(5);
        ___qtablewidgetitem31->setText(QCoreApplication::translate("integration", "ACTIONS", nullptr));
        sbLogoProj->setText(QCoreApplication::translate("integration", "HN", nullptr));
        sbBrandProj->setText(QCoreApplication::translate("integration", "HACKNOVA", nullptr));
        sbSubProj->setText(QCoreApplication::translate("integration", "SMART HACKATHON", nullptr));
        navDashboardProjets->setText(QCoreApplication::translate("integration", "DASHBOARD", nullptr));
        navEmployesProjets->setText(QCoreApplication::translate("integration", "EMPLOYES", nullptr));
        navSallesProjets->setText(QCoreApplication::translate("integration", "SALLES", nullptr));
        navEvaluateursProjets->setText(QCoreApplication::translate("integration", "EVALUATEURS", nullptr));
        navParticipantsProjets->setText(QCoreApplication::translate("integration", "PARTICIPANTS", nullptr));
        navSponsorsProjets->setText(QCoreApplication::translate("integration", "SPONSORS", nullptr));
        navProjetsProjets->setText(QCoreApplication::translate("integration", "PROJETS", nullptr));
        navDeconnexionProjets->setText(QCoreApplication::translate("integration", "DECONNEXION", nullptr));
        topbarTitleProj->setText(QCoreApplication::translate("integration", "Gestion des projets", nullptr));
        topbarSubProj->setText(QCoreApplication::translate("integration", "Suivez, \303\251valuez et validez les projets des participants", nullptr));
        cardProjTitle1->setText(QCoreApplication::translate("integration", "TOTAL PROJETS", nullptr));
        cardProjValue1->setText(QCoreApplication::translate("integration", "0", nullptr));
        cardProjSub1->setText(QCoreApplication::translate("integration", "Projets enregistr\303\251s", nullptr));
        cardProjTitle2->setText(QCoreApplication::translate("integration", "PROJETS TERMINES", nullptr));
        cardProjValue2->setText(QCoreApplication::translate("integration", "0", nullptr));
        cardProjSub2->setText(QCoreApplication::translate("integration", "Dossiers complets", nullptr));
        cardProjTitle3->setText(QCoreApplication::translate("integration", "EN ATTENTE", nullptr));
        cardProjValue3->setText(QCoreApplication::translate("integration", "0", nullptr));
        cardProjSub3->setText(QCoreApplication::translate("integration", "\303\200 compl\303\251ter", nullptr));
        cardProjTitle4->setText(QCoreApplication::translate("integration", "EN COURS", nullptr));
        cardProjValue4->setText(QCoreApplication::translate("integration", "0", nullptr));
        cardProjSub4->setText(QCoreApplication::translate("integration", "En d\303\251veloppement", nullptr));
        formTitleProj->setText(QCoreApplication::translate("integration", "Ajouter / Modifier un projet", nullptr));
        lblProjID->setText(QCoreApplication::translate("integration", "ID", nullptr));
        lblProjNom->setText(QCoreApplication::translate("integration", "NOM DU PROJET", nullptr));
        lblProjCat->setText(QCoreApplication::translate("integration", "CATEGORIE", nullptr));
        lblProjStatut->setText(QCoreApplication::translate("integration", "STATUT", nullptr));
        lblProjEquipe->setText(QCoreApplication::translate("integration", "EQUIPE", nullptr));
        lineEditProjID->setPlaceholderText(QCoreApplication::translate("integration", "Auto", nullptr));
        lineEditProjNom->setPlaceholderText(QCoreApplication::translate("integration", "Nom du projet", nullptr));
        comboBoxProjCategorie->setItemText(0, QCoreApplication::translate("integration", "IA / ML", nullptr));
        comboBoxProjCategorie->setItemText(1, QCoreApplication::translate("integration", "Web", nullptr));
        comboBoxProjCategorie->setItemText(2, QCoreApplication::translate("integration", "Mobile", nullptr));
        comboBoxProjCategorie->setItemText(3, QCoreApplication::translate("integration", "IoT", nullptr));
        comboBoxProjCategorie->setItemText(4, QCoreApplication::translate("integration", "Autre", nullptr));

        comboBoxProjStatut->setItemText(0, QCoreApplication::translate("integration", "En attente", nullptr));
        comboBoxProjStatut->setItemText(1, QCoreApplication::translate("integration", "En cours", nullptr));
        comboBoxProjStatut->setItemText(2, QCoreApplication::translate("integration", "Termin\303\251", nullptr));

        lineEditProjEquipe->setPlaceholderText(QCoreApplication::translate("integration", "\303\211quipe", nullptr));
        btnProjAjouter->setText(QCoreApplication::translate("integration", "AJOUTER", nullptr));
        btnProjModifier->setText(QCoreApplication::translate("integration", "MODIFIER", nullptr));
        btnProjSupprimer->setText(QCoreApplication::translate("integration", "SUPPRIMER", nullptr));
        btnProjConsulter->setText(QCoreApplication::translate("integration", "CONSULTER", nullptr));
        lineEditRechercheProj->setPlaceholderText(QCoreApplication::translate("integration", "Rechercher un projet...", nullptr));
        btnProjRechercher->setText(QCoreApplication::translate("integration", "RECHERCHER", nullptr));
        btnProjTrier->setText(QCoreApplication::translate("integration", "TRIER", nullptr));
        tableTitleProj->setText(QCoreApplication::translate("integration", "Liste des projets", nullptr));
        QTableWidgetItem *___qtablewidgetitem32 = tableWidgetProjets->horizontalHeaderItem(0);
        ___qtablewidgetitem32->setText(QCoreApplication::translate("integration", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem33 = tableWidgetProjets->horizontalHeaderItem(1);
        ___qtablewidgetitem33->setText(QCoreApplication::translate("integration", "NOM DU PROJET", nullptr));
        QTableWidgetItem *___qtablewidgetitem34 = tableWidgetProjets->horizontalHeaderItem(2);
        ___qtablewidgetitem34->setText(QCoreApplication::translate("integration", "CATEGORIE", nullptr));
        QTableWidgetItem *___qtablewidgetitem35 = tableWidgetProjets->horizontalHeaderItem(3);
        ___qtablewidgetitem35->setText(QCoreApplication::translate("integration", "STATUT", nullptr));
        QTableWidgetItem *___qtablewidgetitem36 = tableWidgetProjets->horizontalHeaderItem(4);
        ___qtablewidgetitem36->setText(QCoreApplication::translate("integration", "EQUIPE", nullptr));
        QTableWidgetItem *___qtablewidgetitem37 = tableWidgetProjets->horizontalHeaderItem(5);
        ___qtablewidgetitem37->setText(QCoreApplication::translate("integration", "ACTIONS", nullptr));
    } // retranslateUi

};

namespace Ui {
    class integration: public Ui_integration {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INTEGRATION_H
