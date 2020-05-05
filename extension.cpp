#include "extension.h"
#include <tier0/icommandline.h>

/**
 * @file extension.cpp
 * @brief Implement extension code here.
 */

ExtendedCommandLine g_extendedCmdLine;		/**< Global singleton for extension's main interface */

SMEXT_LINK(&g_extendedCmdLine);

static cell_t sm_CommandLine_Check(IPluginContext *pContext, const cell_t *params)
{
	ICommandLine* pCmdLine = gamehelpers->GetValveCommandLine();
	if (pCmdLine == NULL)
	{
		return pContext->ThrowNativeError("Unable to get valve command line");
	}

	char *param = NULL;
	pContext->LocalToString(params[1], &param);

	const char *value = NULL;
	const char* output = pCmdLine->CheckParm(param, &value);
	return pContext->StringToLocal(params[3], params[4], output);
}

static cell_t sm_CommandLine_Remove(IPluginContext *pContext, const cell_t *params)
{
	ICommandLine* pCmdLine = gamehelpers->GetValveCommandLine();
	if (pCmdLine == NULL)
	{
		return pContext->ThrowNativeError("Unable to get valve command line");
	}

	char *param = NULL;
	pContext->LocalToString(params[1], &param);

	pCmdLine->RemoveParm(param);
	return 1;
}

static cell_t sm_CommandLine_Append(IPluginContext *pContext, const cell_t *params)
{
	ICommandLine* pCmdLine = gamehelpers->GetValveCommandLine();
	if (pCmdLine == NULL)
	{
		return pContext->ThrowNativeError("Unable to get valve command line");
	}

	char *param = NULL;
	char *value = NULL;
	pContext->LocalToString(params[1], &param);
	pContext->LocalToString(params[2], &value);

	pCmdLine->AppendParm(param, value);
	return 1;
}

static cell_t sm_CommandLine_Count(IPluginContext *pContext, const cell_t *params)
{
	ICommandLine* pCmdLine = gamehelpers->GetValveCommandLine();
	if (pCmdLine == NULL)
	{
		return pContext->ThrowNativeError("Unable to get valve command line");
	}

	return pCmdLine->ParmCount();
}

static cell_t sm_CommandLine_Find(IPluginContext *pContext, const cell_t *params)
{
	ICommandLine* pCmdLine = gamehelpers->GetValveCommandLine();
	if (pCmdLine == NULL)
	{
		return pContext->ThrowNativeError("Unable to get valve command line");
	}

	char *param = NULL;
	pContext->LocalToString(params[1], &param);

	return pCmdLine->FindParm(param);
}

static cell_t sm_CommandLine_Get(IPluginContext *pContext, const cell_t *params)
{
	ICommandLine* pCmdLine = gamehelpers->GetValveCommandLine();
	if (pCmdLine == NULL)
	{
		return pContext->ThrowNativeError("Unable to get valve command line");
	}

	int index = params[1];
	const char* value = pCmdLine->GetParm(index);

	return pContext->StringToLocal(params[2], params[3], value);
}

static sp_nativeinfo_t nativeFunctions[] = {
	{"ExtendedCommandLine_Check",		sm_CommandLine_Check},
	{"ExtendedCommandLine_Remove",		sm_CommandLine_Remove},
	{"ExtendedCommandLine_Append",		sm_CommandLine_Append},
	{"ExtendedCommandLine_Count",		sm_CommandLine_Count},
	{"ExtendedCommandLine_Find",		sm_CommandLine_Find},
	{"ExtendedCommandLine_Get",			sm_CommandLine_Get},
	{NULL,											NULL}
};

bool ExtendedCommandLine::SDK_OnLoad(char *error, size_t maxlen, bool late)
{
	sharesys->AddNatives(myself, nativeFunctions);
	return true;
}
