// MotoCom.h
#define DECSPCEX __declspec( dllexport )

#ifdef __cplusplus
extern "C"
{
#endif
////////////////////////// Open ///////////
#define PACKETCOM (1)
#define PACKETLPT (2)
#define PACKETHSLSERVER (3)
#define PACKETHSLCLIENT (4)

#define PACKETETHERNET (16)

/****************************************************/
/****************   BSC     *************************/
/****************************************************/
/* bsc3.h */
/*  "COM1:9600,E,8,1" */
DECSPCEX short APIENTRY BscOpen(char *path,short mode);
DECSPCEX short APIENTRY BscClose(short nCid);
DECSPCEX short APIENTRY BscSetCom(short nCid,short port,DWORD baud,short parity,short clen,short stp);
DECSPCEX short APIENTRY BscSetHSL(short nCid,LPCTSTR strName,short port);
DECSPCEX short APIENTRY BscConnect(short nCid);
DECSPCEX short APIENTRY BscDisConnect(short nCid);
DECSPCEX short APIENTRY BscDownLoad(short nCid,char *fname);
DECSPCEX short APIENTRY BscUpLoad(short nCid,char *fname);
DECSPCEX short APIENTRY BscCommand(short nCid,char *h_buf,char *d_buf,short fforever);
DECSPCEX short APIENTRY BscStatus(short nCid,char *hpt,char *dpt,unsigned short sz,char *rbuf);
DECSPCEX short APIENTRY BscGetStatus(short nCid,WORD *d1,WORD *d2);
DECSPCEX short APIENTRY BscIsError(short nCid);
DECSPCEX short APIENTRY BscIsErrorCode(short nCid);
DECSPCEX short APIENTRY BscSelectJob(short nCid,char *name);
DECSPCEX short APIENTRY BscStartJob(short nCid);
DECSPCEX short APIENTRY BscContinueJob(short nCid);
DECSPCEX short APIENTRY BscHoldOn(short nCid);
DECSPCEX short APIENTRY BscHoldOff(short nCid);
DECSPCEX short APIENTRY BscCancel(short nCid);
DECSPCEX short APIENTRY BscDeleteJob(short nCid);
DECSPCEX short APIENTRY BscSetMasterJob(short nCid);
DECSPCEX short APIENTRY BscSetLineNumber(short nCid,short line);
DECSPCEX short APIENTRY BscSelStepCycle(short nCid);
DECSPCEX short APIENTRY BscSelOneCycle(short nCid);
DECSPCEX short APIENTRY BscSelLoopCycle(short nCid);
DECSPCEX short APIENTRY BscServoOn(short nCid);
DECSPCEX short APIENTRY BscServoOff(short nCid);
DECSPCEX short APIENTRY BscOPLock(short nCid);
DECSPCEX short APIENTRY BscOPUnLock(short nCid);
DECSPCEX short APIENTRY BscIsHold(short nCid);
DECSPCEX short APIENTRY BscJobWait(short nCid,short time);
DECSPCEX short APIENTRY BscMDSP(short nCid,char *ptr);
DECSPCEX short APIENTRY BscConvertJobP2R(short nCid,char *name,char *framename);
DECSPCEX short APIENTRY BscGetError(short nCid);
DECSPCEX short APIENTRY BscGetError2(short nCid);//990224 Sakasegawa for XRC
DECSPCEX short APIENTRY BscGetFirstAlarm(short nCid,WORD *data);
DECSPCEX short APIENTRY BscGetNextAlarm(short nCid, WORD *data);
DECSPCEX short APIENTRY BscIsLoc(short nCid,short ispulse,WORD *rconf,double *p);
DECSPCEX short APIENTRY BscIsCycle(short nCid);
DECSPCEX short APIENTRY BscIsPlayMode(short nCid);
DECSPCEX short APIENTRY BscIsAlarm(short nCid);
DECSPCEX short APIENTRY BscIsServo(short nCid);
DECSPCEX short APIENTRY BscIsJobName(short nCid,char *jobname,short size);
DECSPCEX short APIENTRY BscIsJobLine(short nCid);
DECSPCEX short APIENTRY BscIsJobStep(short nCid);
DECSPCEX short APIENTRY BscFindFirst(short nCid,char *fname,short size);
DECSPCEX short APIENTRY BscFindNext(short nCid,char *fname,short size);
DECSPCEX short APIENTRY BscFindFirstMaster(short nCid,char *fname,short size);
DECSPCEX short APIENTRY BscFindNextMaster(short nCid,char *fname,short size);
DECSPCEX short APIENTRY BscDCILoadSave(short nCid,short timec);
DECSPCEX short APIENTRY BscDCILoadSaveOnce(short nCid);
DECSPCEX short APIENTRY BscDCIGetPos(short nCid,WORD *type,WORD *rconf,double *p);
DECSPCEX short APIENTRY BscDCIPutPos(short nCid,WORD type,WORD rconf,double *p);
DECSPCEX short APIENTRY BscPuts(short nCid,char *bufptr,WORD length);
DECSPCEX short APIENTRY BscGets(short nCid,char *bufptr,WORD bsize,WORD *plengets);
DECSPCEX short APIENTRY BscInBytes(short nCid);
DECSPCEX short APIENTRY BscOutBytes(short nCid);
DECSPCEX short APIENTRY BscDelay(short nCid,DWORD a);
DECSPCEX short APIENTRY BscSetCondBSC(short nCid,short timerA,short timerB,short rtyR,short rtyW);
DECSPCEX short APIENTRY BscSetBreak(short nCid,short flg);

DECSPCEX short APIENTRY BscConvertJobR2P(short nCid,char *name,short cv_type,char *var_no);
DECSPCEX short APIENTRY BscGetVarData(short nCid,short type,short varno,double *pos);
DECSPCEX short APIENTRY BscPutVarData(short nCid,short type,short varno,double *dat);
DECSPCEX short APIENTRY BscReset(short nCid);
DECSPCEX short APIENTRY BscSelectMode(short nCid,short mode);
DECSPCEX short APIENTRY BscIsCtrlGroup(short nCid);
DECSPCEX short APIENTRY BscIsTaskInf(short nCid);
DECSPCEX short APIENTRY BscGetCtrlGroup(short nCid,WORD *groupinf,WORD *taskinf);
DECSPCEX short APIENTRY BscSetCtrlGroup(short nCid,WORD groupno);

//---> XRC �`�ԏ��`���Ή�
DECSPCEX short APIENTRY BscIsCtrlGroupXrc(short nCid, WORD *robtask,WORD *stattask);
DECSPCEX short APIENTRY BscIsTaskInfXrc(short nCid);
DECSPCEX short APIENTRY BscGetCtrlGroupXrc(short nCid,WORD *robtask,WORD *stattask,WORD *taskinf);
DECSPCEX short APIENTRY BscSetCtrlGroupXrc(short nCid,WORD groupno1, WORD groupno2);
// <---

DECSPCEX short APIENTRY BscChangeTask(short nCid,short task);
DECSPCEX short APIENTRY BscGetUFrame(short nCid,char *ufname,double *p);
DECSPCEX short APIENTRY BscPutUFrame(short nCid,char *ufname,double *p);
DECSPCEX short APIENTRY BscMovj(short nCid,double spd,char *framename,short rconf,short toolno,double *p);
DECSPCEX short APIENTRY BscMovl(short nCid,char *vtype,double spd,char *framename,short rconf,short toolno,double *p);
DECSPCEX short APIENTRY BscImov(short nCid,char *vtype,double spd,char *framename,short toolno,double *p);
DECSPCEX short APIENTRY BscMov(short nCid,char *movtype,char *vtype,double spd,char *framename,short rconf,short toolno,double *p);
DECSPCEX short APIENTRY BscPMovj(short nCid,double spd,short toolno,double *p);
DECSPCEX short APIENTRY BscPMovl(short nCid,char *vtype,double spd,short toolno,double *p);
DECSPCEX short APIENTRY BscPMov(short nCid,char *movtype,char *vtype,double spd,short toolno,double *p);
DECSPCEX short APIENTRY BscIsTeachMode(short nCid);
DECSPCEX short APIENTRY BscIsRemoteMode(short nCid);
DECSPCEX short APIENTRY BscIsRobotPos(short nCid,char *framename,short isex,WORD *rconf,WORD *toolno,double *p);
/****************************************************/
DECSPCEX short APIENTRY BscDiskFreeSizeGet(short nCid,short dno,long *dsize);
DECSPCEX short APIENTRY BscReadIO(short nCid,WORD startadd,WORD ionum,WORD *stat);
DECSPCEX short APIENTRY BscWriteIO(short nCid,WORD startadd,WORD ionum,WORD *stat);

/****************************************************/
//970909
DECSPCEX short APIENTRY BscGetAbso(short nCid,short axisno,long *abso);
DECSPCEX short APIENTRY BscSetAbso(short nCid,short axisno,long abso);

/****************************************************/
//970606
DECSPCEX short APIENTRY BscSetEther( short nCid, char FAR *IPaddr, short mode, HWND hWnd);

/****************************************************/
//981019
DECSPCEX short APIENTRY BscDownLoadEx(short nCid,char *fname, char *srcPath, BOOL nFlg);
DECSPCEX short APIENTRY BscUpLoadEx(short nCid,char *fname, char *desPath, BOOL nFlg);

/****************************************************/
/****************   FC1,FC2 *************************/
/****************************************************/
/* FCWIN.H */
/*************** Slave Command /I am FC1. ***********************/
/* DOS  COM1:96,E,8,1 */
/* Win FC1 COM1:4800,E,8,1 */
/* Win FC2 COM1:19200,E,8,1 */
DECSPCEX short APIENTRY FcOpen(char *path,short mode);
DECSPCEX short APIENTRY FcClose(short nCid);
DECSPCEX short APIENTRY FcSetCom(short nCid,short port,DWORD baud,short parity,short clen,short stp);
DECSPCEX short APIENTRY FcSetHSL(short nCid,LPCTSTR strName,short port);
DECSPCEX short APIENTRY FcConnect(short nCid);
DECSPCEX short APIENTRY FcDisConnect(short nCid);
DECSPCEX short APIENTRY FcScan(short nCid);
DECSPCEX short APIENTRY FcProc(short nCid,short isremove);
DECSPCEX short APIENTRY FcGetCom(short nCid,char *buf,short size);
DECSPCEX short APIENTRY FcGetData(short nCid,char *buf,short size);
DECSPCEX short APIENTRY FcSetBreak(short nCid,short flg);

/* FC1�Ή� */
DECSPCEX short APIENTRY FcGetPath(short nCid,char *buf,short size);
/*************** Master Command /I am ERC.***********************/
DECSPCEX short APIENTRY FcLogin(short nCid);
DECSPCEX short APIENTRY FcLogout(short nCid);
DECSPCEX short APIENTRY FcBye(short nCid);
DECSPCEX short APIENTRY FcDiskSize(short nCid,char *disksize,short size);
DECSPCEX short APIENTRY FcFileSize(short nCid,char *fname,long *size);
DECSPCEX short APIENTRY FcUpload(short nCid,char *fname);
DECSPCEX short APIENTRY FcDownload(short nCid,char *fname);
DECSPCEX short APIENTRY FcRemove(short nCid,char *fname);
DECSPCEX short APIENTRY FcRename(short nCid,char *oldname,char *newname);
DECSPCEX short APIENTRY FcFindFirst(short nCid,char *fname,short size);
DECSPCEX short APIENTRY FcFindNext(short nCid,char *fname,short size);
DECSPCEX short APIENTRY FcFindCurrentDir(short nCid,char *dname,short size);
DECSPCEX short APIENTRY FcFindFirstDir(short nCid,char *dname,short size);
DECSPCEX short APIENTRY FcFindNextDir(short nCid,char *dname,short size);
DECSPCEX short APIENTRY FcMakeDir(short nCid,char *dname);
DECSPCEX short APIENTRY FcChangeDir(short nCid,char *dname);
DECSPCEX short APIENTRY FcChangeDrive(short nCid,char *type);
DECSPCEX short APIENTRY FcAutoDeleteSet(short nCid,short flg);
DECSPCEX short APIENTRY FcDiskSizeSet(short nCid,short flg);
DECSPCEX short APIENTRY FcIsDiskSize(short nCid);

// �Đڑ�����
DECSPCEX short APIENTRY BscReConnect(short nCid);
// �����۰�ޏ���
DECSPCEX short APIENTRY BscEnforcedClose(short nCid);

#ifdef __cplusplus
}
#endif
