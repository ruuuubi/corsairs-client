#include "StdAfx.h"
#include "uistateform.h"
#include "uiformmgr.h"
#include "uilabel.h"
#include "uitextbutton.h"
#include "gameapp.h"
#include "character.h"
#include "uiprogressbar.h"
#include "commfunc.h"
#include "ChaAttr.h"
#include "procirculate.h"
#include "packetcmd.h"
#include "tools.h"
#include "GuildData.h"
#include "uiboatform.h"

using namespace GUI;
//---------------------------------------------------------------------------
// class CStateMgr
//---------------------------------------------------------------------------
bool CStateMgr::Init()
{
	CFormMgr &mgr = CFormMgr::s_Mgr;

	frmState = _FindForm("frmState");  //属性表单 
	if( !frmState )		return false;
	frmState->evtShow = _evtMainShow;

	//frmState 内的控件列表
	labStateName  = dynamic_cast<CLabelEx*>(frmState->Find("labStateName"));    
	if( !labStateName )		return Error( g_oLangRec.GetString(45), frmState->GetName(), "labStateName" );
	labStateName->SetIsCenter(true);

	FORM_CONTROL_LOADING_CHECK(labGuildName,frmState,CLabelEx,"preperty.clu","labStateGuid");

	labStateJob  = dynamic_cast<CLabelEx*>(frmState->Find("labStateJob"));    
	if( !labStateJob )		return Error( g_oLangRec.GetString(45), frmState->GetName(), "labStateJob" );

	labStateLevel  = dynamic_cast<CLabelEx*>(frmState->Find("labStateLevel"));    
	if( !labStateLevel)		return Error( g_oLangRec.GetString(45), frmState->GetName(), "labStateLevel" );

	labStatePoint  = dynamic_cast<CLabelEx*>(frmState->Find("labStatePoint"));    
	if( !labStatePoint )	return Error( g_oLangRec.GetString(45), frmState->GetName(), "labStatePoint" );
	
	labSkillPoint  = dynamic_cast<CLabelEx*>(frmState->Find("labSkillPoint"));    
	if( !labSkillPoint )	return Error( g_oLangRec.GetString(45), frmState->GetName(), "labSkillPoint" );

	labFameShow  = dynamic_cast<CLabelEx*>(frmState->Find("labFameShow"));    
	if( !labFameShow )   	return Error( g_oLangRec.GetString(45), frmState->GetName(), "labFameShow" );

	//6个
	btnStr  = dynamic_cast<CTextButton *>(frmState->Find("btnStr"));    
	if( !btnStr )   		return Error( g_oLangRec.GetString(45), frmState->GetName(), "btnStr" );
	btnStr->evtMouseClick = MainMouseDown;

	btnAgi  = dynamic_cast<CTextButton *>(frmState->Find("btnAgi"));    
	if( !btnAgi )			return Error( g_oLangRec.GetString(45), frmState->GetName(), "btnAgi" );
	btnAgi->evtMouseClick = MainMouseDown;

	btnCon  = dynamic_cast<CTextButton *>(frmState->Find("btnCon"));    
	if( !btnCon )			return Error( g_oLangRec.GetString(45), frmState->GetName(), "btnCon" );
	btnCon->evtMouseClick = MainMouseDown;

	btnSta  = dynamic_cast<CTextButton *>(frmState->Find("btnSta"));    
	if( !btnSta )			return Error( g_oLangRec.GetString(45), frmState->GetName(), "btnSta" );
	btnSta->evtMouseClick = MainMouseDown;

	//btnLuk  = dynamic_cast<CTextButton *>(frmState->Find("btnLuk"));    
	//if( !btnLuk )			return Error( "msgui.clu界面<%s>上找不到控件<%s>", frmState->GetName(), "btnLuk" );
	//btnLuk->evtMouseClick = MainMouseDown;

	btnDex  = dynamic_cast<CTextButton *>(frmState->Find("btnDex"));    
	if( !btnDex )			return Error( g_oLangRec.GetString(45), frmState->GetName(), "btnDex" );
	btnDex->evtMouseClick = MainMouseDown;

	//frmState下的进度条控件
	labStateEXP  = dynamic_cast<CLabelEx*>(frmState->Find("labStateEXP"));    
	if( !labStateEXP )
		return Error( g_oLangRec.GetString(45), frmState->GetName(), "labStateEXP" );
	labStateEXP->SetIsCenter(true);

	labStateHP  = dynamic_cast<CLabelEx*>(frmState->Find("labStateHP"));    
	if( !labStateHP )
		return Error( g_oLangRec.GetString(45), frmState->GetName(), "labStateHP" );
	labStateHP->SetIsCenter(true);

	labStateSP  = dynamic_cast<CLabelEx*>(frmState->Find("labStateSP"));    
	if( !labStateSP )
		return Error( g_oLangRec.GetString(45), frmState->GetName(), "labStateSP" );
	labStateSP->SetIsCenter(true);


	//6个基本属性
	labStrshow  = 	( CLabelEx *)frmState->Find( "labStrshow" );
	labDexshow  = 	( CLabelEx *)frmState->Find( "labDexshow" );
	labAgishow  = 	( CLabelEx *)frmState->Find( "labAgishow" );
	labConshow  = 	( CLabelEx *)frmState->Find( "labConshow" );
	labStashow  = 	( CLabelEx *)frmState->Find( "labStashow" );
	//labLukshow  = 	( CLabelEx *)frmState->Find( "labLukshow" );
	labSailLevel  = 	( CLabelEx *)frmState->Find( "labSailLevel" );
	labSailEXP  = 	( CLabelEx *)frmState->Find( "labSailEXP" );

	//8个附加属性
	labMinAtackShow  = 	( CLabelEx *)frmState->Find( "labMinAtackShow" );
	labMaxAtackShow  = 	( CLabelEx *)frmState->Find( "labMaxAtackShow" );
	labFleeShow      = 	( CLabelEx *)frmState->Find( "labFleeShow" );
	labAspeedShow    = 	( CLabelEx *)frmState->Find( "labAspeedShow" );
	labMspeedShow    = 	( CLabelEx *)frmState->Find( "labMspeedShow" );
	labHitShow       = 	( CLabelEx *)frmState->Find( "labHitShow" );
	labDefenceShow   = 	( CLabelEx *)frmState->Find( "labDefenceShow" );
	//labCriticalShow  = 	( CLabelEx *)frmState->Find( "labCriticalShow" );
	//labMfShow        = 	( CLabelEx *)frmState->Find( "labMfShow" );
	labPhysDefineShow=  ( CLabelEx *)frmState->Find( "labPhysDefineShow" );
	return true;


}

void CStateMgr::End()
{
}

void CStateMgr::FrameMove(DWORD dwTime)
{
	if( frmState->GetIsShow() )
	{
		static CTimeWork time(100);
		if( time.IsTimeOut( dwTime ) )
			RefreshStateFrm();
	}
}

void CStateMgr::_evtMainShow(CGuiData *pSender)
{
	g_stUIState.RefreshStateFrm();
}

void CStateMgr::RefreshStateFrm()
{
	CForm * f = g_stUIState.frmState;
	if( !f->GetIsShow() )	return;

	CCharacter* pCha = g_stUIBoat.GetHuman();
	if( !pCha )			return;

	SGameAttr* pCChaAttr = pCha->getGameAttr();
	if (!pCChaAttr )	return;

	char  pszCha[256] = { 0 };

	// 血条
	if (labStateHP)     
	{
		sprintf( pszCha , "%d/%d", pCChaAttr->get(ATTR_HP), pCChaAttr->get(ATTR_MXHP) );
		labStateHP->SetCaption( pszCha );
	}

	// 玩家经验
	int num = pCChaAttr->get(ATTR_CEXP);
	int curlev = pCChaAttr->get( ATTR_CLEXP);
	int nextlev = pCChaAttr->get( ATTR_NLEXP);

	int max = nextlev - curlev;
	num = num - curlev;
	if ( num < 0 ) num = 0;

	if ( labStateEXP)
	{
		if (max!=0)
			sprintf( pszCha , "%4.2f%%" , num*100.0f/max );	
		else 
			sprintf( pszCha , "0.00%");

		labStateEXP->SetCaption( pszCha );
	}

	// 魔法
	num = pCChaAttr->get(ATTR_SP);
	max = pCChaAttr->get(ATTR_MXSP);
	if (labStateSP)
	{
		sprintf( pszCha, "%d/%d", num, max );
        labStateSP->SetCaption( pszCha );	
	}

	//玩家名称
	if(labStateName)		
	{
		sprintf( pszCha , "%s", pCha->getName());
		labStateName->SetCaption( (const char* ) pszCha) ;
	}

	//公会
	if (labGuildName)
	{
		if (CGuildData::GetGuildID())
		{
			labGuildName->SetCaption(CGuildData::GetGuildName().c_str());
		}
		else
		{
			labGuildName->SetCaption("");
		}
	}

	//玩家职业
	if(labStateJob)			
	{
		sprintf(pszCha,"%s",	g_GetJobName((short)pCChaAttr->get(ATTR_JOB)));
		labStateJob->SetCaption( (const char* ) pszCha);
	}

	//玩家等级
	if(labStateLevel)		
	{
		sprintf( pszCha , "%d", pCChaAttr->get(ATTR_LV));				 //显示角色等级
		labStateLevel->SetCaption( (const char* ) pszCha);
	}

	//玩家属性点
	if(labStatePoint)		
	{
		sprintf( pszCha , "%d", pCChaAttr->get(ATTR_AP) );				//显示角色的属性点			
		labStatePoint->SetCaption( (const char* ) pszCha);
	}

	if(labSkillPoint)		
	{
		sprintf( pszCha , "%d", pCChaAttr->get(ATTR_TP));	             //显示角色的技能点		
		labSkillPoint->SetCaption( (const char* ) pszCha);
	}

	//属性点大于0，则显示6个基本属性按钮
	if ( pCChaAttr->get(ATTR_AP)>0  )	
	{
		btnStr->SetIsShow(true);
		btnAgi->SetIsShow(true); 
		btnCon->SetIsShow(true); 
		btnSta->SetIsShow(true); 
		//btnLuk->SetIsShow(true); 
		btnDex->SetIsShow(true);
	}
	else
	{
		btnStr->SetIsShow(false);
		btnAgi->SetIsShow(false); 
		btnCon->SetIsShow(false); 
		btnSta->SetIsShow(false); 
		//btnLuk->SetIsShow(false); 
		btnDex->SetIsShow(false);
	}
	//6个基本属性
	if(labStrshow)		
	{
		sprintf( pszCha , "%d" , pCChaAttr->get(ATTR_STR));
		labStrshow->SetCaption( (const char* ) pszCha);
	}

	if(labDexshow)		
	{
		sprintf( pszCha , "%d" , pCChaAttr->get(ATTR_DEX));
		labDexshow->SetCaption( (const char* ) pszCha);
	}

	if(labAgishow)		
	{
		sprintf( pszCha , "%d" , pCChaAttr->get(ATTR_AGI));
		labAgishow->SetCaption( (const char* ) pszCha);
	}

	if(labConshow)		
	{
		sprintf( pszCha , "%d" , pCChaAttr->get(ATTR_CON));
		labConshow->SetCaption( (const char* ) pszCha);
	}

	if(labStashow)		
	{
		sprintf( pszCha, "%d" , pCChaAttr->get(ATTR_STA));
		labStashow->SetCaption( (const char* ) pszCha);
	}

	if(labSailLevel)		
	{
		sprintf( pszCha, "%d" , pCChaAttr->get(ATTR_SAILLV));
		labSailLevel->SetCaption( (const char* ) pszCha);
	}

	if(labSailEXP)		
	{
		sprintf( pszCha, "%d" , pCChaAttr->get(ATTR_CSAILEXP));
		labSailEXP->SetCaption( (const char* ) pszCha);
	}

	//sprintf( pszCha , "%d" , pCChaAttr->get(ATTR_LUK));
	//if(labLukshow)		labLukshow->SetCaption( (const char* ) pszCha);

	//8个附加属性
	if(labMinAtackShow)		
	{
		sprintf( pszCha , "%d" , pCChaAttr->get(ATTR_MNATK));// 最小攻击力		
		labMinAtackShow->SetCaption( (const char* ) pszCha);
	}

	if(labMaxAtackShow)		
	{
		sprintf( pszCha , "%d" , pCChaAttr->get(ATTR_MXATK));// 最大攻击力
		labMaxAtackShow->SetCaption( (const char* ) pszCha);
	}

	if(labFleeShow)			
	{
		sprintf( pszCha , "%d" , pCChaAttr->get(ATTR_FLEE)); // 闪避率
		labFleeShow->SetCaption( (const char* ) pszCha);
	}

	if(labAspeedShow)		
	{		
		int v = pCChaAttr->get(ATTR_ASPD);
		if( v==0 )
			sprintf( pszCha , "-1" );
		else
			sprintf( pszCha , "%d" , 100000 / v);// 攻击间隔

		labAspeedShow->SetCaption( (const char* ) pszCha);
	}
	
	if(labMspeedShow)		
	{		
		sprintf( pszCha , "%d" , pCChaAttr->get(ATTR_MSPD));
		labMspeedShow->SetCaption( (const char* ) pszCha);
	}

	if(labHitShow)			
	{
		sprintf( pszCha , "%d" , pCChaAttr->get(ATTR_HIT)); // 命中率
		labHitShow->SetCaption( (const char* ) pszCha);
	}

	if(labDefenceShow)		
	{
		sprintf( pszCha , "%d" , pCChaAttr->get(ATTR_DEF)); // 防御力
		labDefenceShow->SetCaption( (const char* ) pszCha);
	}

	//if(labCriticalShow)		
	//{
	//	sprintf( pszCha , "%d" , pCChaAttr->get(ATTR_CRT)); // 爆击率
	//	labCriticalShow->SetCaption( (const char* ) pszCha);
	//}

	//if(labMfShow)			
	//{
	//	sprintf( pszCha , "%d" , pCChaAttr->get(ATTR_MF));	 // 寻宝率
	//	labMfShow->SetCaption( (const char* ) pszCha);
	//}

	if(labPhysDefineShow)			
	{
		sprintf( pszCha , "%d" , pCChaAttr->get(ATTR_PDEF)); // 物理抵抗
		labPhysDefineShow->SetCaption( (const char* ) pszCha);
	}

	if(labFameShow)
	{
		sprintf(pszCha, "%d", pCChaAttr->get(ATTR_FAME));	// 声望
		labFameShow->SetCaption( (const char* ) pszCha);
	}
}

void CStateMgr::MainMouseDown(CGuiData *pSender, int x, int y, DWORD key)
{
	CCharacter* pCha = g_stUIBoat.GetHuman();
	if( !pCha ) return;	        
	
	if ( pCha->getGameAttr()->get(ATTR_AP)<=0  ) return;

	CChaAttr attr;
	attr.ResetChangeFlag();
	
	string name = pSender->GetName();
	if (name =="btnStr")
	{	
		attr.DirectSetAttr( ATTR_STR, 1);
		attr.SetChangeBitFlag( ATTR_STR );
		CProCirculateCS* proCir = (CProCirculateCS *)g_NetIF->GetProCir();
		proCir->SynBaseAttribute( &attr );		
	}
	else if (name =="btnAgi")
	{						
		attr.DirectSetAttr( ATTR_AGI, 1);
		attr.SetChangeBitFlag( ATTR_AGI );						
		CProCirculateCS* proCir = (CProCirculateCS *)g_NetIF->GetProCir();
		proCir->SynBaseAttribute( &attr );		
	}
	else if (name =="btnCon")
	{
		attr.DirectSetAttr( ATTR_CON, 1);
		attr.SetChangeBitFlag( ATTR_CON );				
		CProCirculateCS* proCir = (CProCirculateCS *)g_NetIF->GetProCir();
		proCir->SynBaseAttribute( &attr );

	}
	else if (name =="btnSta")
	{
		attr.DirectSetAttr( ATTR_STA, 1);
		attr.SetChangeBitFlag( ATTR_STA );	
		CProCirculateCS* proCir = (CProCirculateCS *)g_NetIF->GetProCir();
		proCir->SynBaseAttribute( &attr );
	}
	//else if (name =="btnLuk")
	//{
	//	attr.DirectSetAttr( ATTR_LUK, 1);
	//	attr.SetChangeBitFlag( ATTR_LUK );		
	//	CProCirculateCS* proCir = (CProCirculateCS *)g_NetIF->GetProCir();
	//	proCir->SynBaseAttribute( &attr );

	//}
	else if (name =="btnDex")
	{
		attr.DirectSetAttr( ATTR_DEX, 1);
		attr.SetChangeBitFlag( ATTR_DEX );			
		CProCirculateCS* proCir = (CProCirculateCS *)g_NetIF->GetProCir();
		proCir->SynBaseAttribute( &attr );
	}
}
