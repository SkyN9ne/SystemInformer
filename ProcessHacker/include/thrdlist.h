#ifndef PH_THRDLIST_H
#define PH_THRDLIST_H

#include <phuisup.h>
#include <colmgr.h>

// Columns

typedef enum _PH_THREAD_TREELIST_COLUMN
{
    PH_THREAD_TREELIST_COLUMN_TID,
    PH_THREAD_TREELIST_COLUMN_CPU,
    PH_THREAD_TREELIST_COLUMN_CYCLESDELTA,
    PH_THREAD_TREELIST_COLUMN_STARTADDRESS,
    PH_THREAD_TREELIST_COLUMN_PRIORITYSYMBOLIC,
    PH_THREAD_TREELIST_COLUMN_SERVICE,
    PH_THREAD_TREELIST_COLUMN_NAME,
    PH_THREAD_TREELIST_COLUMN_STARTED,
    PH_THREAD_TREELIST_COLUMN_STARTMODULE,
    PH_THREAD_TREELIST_COLUMN_CONTEXTSWITCHES,
    PH_THREAD_TREELIST_COLUMN_CONTEXTSWITCHESDELTA,
    PH_THREAD_TREELIST_COLUMN_PRIORITY,
    PH_THREAD_TREELIST_COLUMN_BASEPRIORITY,
    PH_THREAD_TREELIST_COLUMN_PAGEPRIORITY,
    PH_THREAD_TREELIST_COLUMN_IOPRIORITY,
    PH_THREAD_TREELIST_COLUMN_CYCLES,
    PH_THREAD_TREELIST_COLUMN_STATE,
    PH_THREAD_TREELIST_COLUMN_KERNELTIME,
    PH_THREAD_TREELIST_COLUMN_USERTIME,
    PH_THREAD_TREELIST_COLUMN_IDEALPROCESSOR,
    PH_THREAD_TREELIST_COLUMN_CRITICAL,
    PH_THREAD_TREELIST_COLUMN_TIDHEX,
    PH_THREAD_TREELIST_COLUMN_CPUCORECYCLES,
    PH_THREAD_TREELIST_COLUMN_TOKEN_STATE,
    PH_THREAD_TREELIST_COLUMN_PENDINGIRP,
    PH_THREAD_TREELIST_COLUMN_LASTSYSTEMCALL,
    PH_THREAD_TREELIST_COLUMN_LASTSTATUSCODE,
    PH_THREAD_TREELIST_COLUMN_TIMELINE,
    PH_THREAD_TREELIST_COLUMN_APARTMENTSTATE,
    PH_THREAD_TREELIST_COLUMN_FIBER,
    PH_THREAD_TREELIST_COLUMN_PRIORITYBOOST,
    PH_THREAD_TREELIST_COLUMN_CPUUSER,
    PH_THREAD_TREELIST_COLUMN_CPUKERNEL,
    //PH_THREAD_TREELIST_COLUMN_CPUHISTORY,
    PH_THREAD_TREELIST_COLUMN_STACKUSAGE,
    PH_THREAD_TREELIST_COLUMN_WAITTIME,
    PH_THREAD_TREELIST_COLUMN_MAXIMUM
} PH_THREAD_TREELIST_COLUMN;

typedef enum _PH_THREAD_TREELIST_MENUITEM
{
    PH_THREAD_TREELIST_MENUITEM_HIDE_SUSPENDED = 1,
    PH_THREAD_TREELIST_MENUITEM_HIDE_GUITHREADS,
    PH_THREAD_TREELIST_MENUITEM_HIDE_UNKNOWNSTARTADDRESS,
    PH_THREAD_TREELIST_MENUITEM_HIGHLIGHT_SUSPENDED,
    PH_THREAD_TREELIST_MENUITEM_HIGHLIGHT_GUITHREADS,
    PH_THREAD_TREELIST_MENUITEM_SAVE, // Always last (dmex)
    PH_THREAD_TREELIST_MENUITEM_MAXIMUM
} PH_THREAD_TREELIST_MENUITEM;

typedef enum _PH_THREAD_TOKEN_STATE
{
    PH_THREAD_TOKEN_STATE_UNKNOWN,
    PH_THREAD_TOKEN_STATE_NOT_PRESENT,
    PH_THREAD_TOKEN_STATE_ANONYMOUS,
    PH_THREAD_TOKEN_STATE_PRESENT
} PH_THREAD_TOKEN_STATE;

// begin_phapppub
typedef struct _PH_THREAD_NODE
{
    PH_TREENEW_NODE Node;

    PH_SH_STATE ShState;

    HANDLE ThreadId;
    PPH_THREAD_ITEM ThreadItem;
// end_phapppub

    PH_STRINGREF TextCache[PH_THREAD_TREELIST_COLUMN_MAXIMUM];

    ULONG ValidMask;

    HANDLE ThreadContextHandle;
    HANDLE ThreadReadVmHandle;
    BOOLEAN ThreadContextHandleValid;
    BOOLEAN ThreadReadVmHandleValid;
    LONG IdealProcessorMask;

    ULONG PagePriority;
    IO_PRIORITY_HINT IoPriority;
    BOOLEAN BreakOnTermination;
    BOOLEAN PendingIrp;
    USHORT LastSystemCallNumber;
    ULONG LastStatusCode;
    ULONG ApartmentState;
    BOOLEAN Fiber;
    BOOLEAN PriorityBoost;
    FLOAT StackUsage;
    PH_THREAD_TOKEN_STATE TokenState;
    WCHAR ThreadIdText[PH_INT32_STR_LEN_1];
    WCHAR CpuUsageText[PH_INT32_STR_LEN_1];
    WCHAR CpuUserUsageText[PH_INT32_STR_LEN_1];
    WCHAR CpuKernelUsageText[PH_INT32_STR_LEN_1];
    PPH_STRING CyclesDeltaText; // used for Context Switches Delta as well
    PPH_STRING ContextSwitchesDeltaText;
    PPH_STRING StartAddressText;
    PPH_STRING PrioritySymbolicText;
    PPH_STRING CreatedText;
    PPH_STRING NameText;
    PPH_STRING StateText;
    PPH_STRING LastSystemCallText;
    PPH_STRING LastErrorCodeText;
    PPH_STRING ApartmentStateText;
    PPH_STRING StackUsageText;
    WCHAR ContextSwitchesText[PH_INT64_STR_LEN_1];
    WCHAR PriorityText[PH_INT32_STR_LEN_1];
    WCHAR BasePriorityText[PH_INT32_STR_LEN_1];
    WCHAR CyclesText[PH_INT64_STR_LEN_1];
    WCHAR KernelTimeText[PH_TIMESPAN_STR_LEN_1];
    WCHAR UserTimeText[PH_TIMESPAN_STR_LEN_1];
    WCHAR IdealProcessorText[PH_INT32_STR_LEN + 1 + PH_INT32_STR_LEN + 1];
    WCHAR ThreadIdHexText[PH_INT32_STR_LEN_1];
    WCHAR CpuCoreUsageText[PH_INT32_STR_LEN_1];
    WCHAR WaitTimeText[PH_TIMESPAN_STR_LEN_1];
// begin_phapppub
} PH_THREAD_NODE, *PPH_THREAD_NODE;
// end_phapppub

typedef struct _PH_THREAD_LIST_CONTEXT
{
    HWND ParentWindowHandle;
    HWND TreeNewHandle;
    ULONG TreeNewSortColumn;
    PH_SORT_ORDER TreeNewSortOrder;
    PH_CM_MANAGER Cm;

    PPH_HASHTABLE NodeHashtable;
    PPH_LIST NodeList;
    PPH_POINTER_LIST NodeStateList;
    PH_TN_FILTER_SUPPORT TreeFilterSupport;

    HANDLE ProcessId;
    LARGE_INTEGER ProcessCreateTime;

    BOOLEAN EnableStateHighlighting;
    BOOLEAN UseCycleTime;
    BOOLEAN HasServices;

    union
    {
        ULONG Flags;
        struct
        {
            ULONG Reserved : 3;

            ULONG HideSuspended : 1;
            ULONG HideGuiThreads : 1;
            ULONG HighlightSuspended : 1;
            ULONG HighlightGuiThreads : 1;

            ULONG Spare : 25;
        };
    };
} PH_THREAD_LIST_CONTEXT, *PPH_THREAD_LIST_CONTEXT;

VOID PhInitializeThreadList(
    _In_ HWND ParentWindowHandle,
    _In_ HWND TreeNewHandle,
    _Out_ PPH_THREAD_LIST_CONTEXT Context
    );

VOID PhDeleteThreadList(
    _In_ PPH_THREAD_LIST_CONTEXT Context
    );

VOID PhLoadSettingsThreadList(
    _Inout_ PPH_THREAD_LIST_CONTEXT Context
    );

VOID PhSaveSettingsThreadList(
    _Inout_ PPH_THREAD_LIST_CONTEXT Context
    );

VOID PhSetOptionsThreadList(
    _Inout_ PPH_THREAD_LIST_CONTEXT Context,
    _In_ ULONG Options
    );

PPH_THREAD_NODE PhAddThreadNode(
    _Inout_ PPH_THREAD_LIST_CONTEXT Context,
    _In_ PPH_THREAD_ITEM ThreadItem,
    _In_ BOOLEAN FirstRun
    );

PPH_THREAD_NODE PhFindThreadNode(
    _In_ PPH_THREAD_LIST_CONTEXT Context,
    _In_ HANDLE ThreadId
    );

VOID PhRemoveThreadNode(
    _In_ PPH_THREAD_LIST_CONTEXT Context,
    _In_ PPH_THREAD_NODE ThreadNode
    );

VOID PhUpdateThreadNode(
    _In_ PPH_THREAD_LIST_CONTEXT Context,
    _In_ PPH_THREAD_NODE ThreadNode
    );

VOID PhTickThreadNodes(
    _In_ PPH_THREAD_LIST_CONTEXT Context
    );

PPH_THREAD_ITEM PhGetSelectedThreadItem(
    _In_ PPH_THREAD_LIST_CONTEXT Context
    );

VOID PhGetSelectedThreadItems(
    _In_ PPH_THREAD_LIST_CONTEXT Context,
    _Out_ PPH_THREAD_ITEM **Threads,
    _Out_ PULONG NumberOfThreads
    );

VOID PhDeselectAllThreadNodes(
    _In_ PPH_THREAD_LIST_CONTEXT Context
    );

#endif
