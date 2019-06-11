// 8 june 2019
#include "test.h"

#if 0

struct testOSImplData {
	bool initCalled;
	bool *freeCalled;
	bool testMethodCalled;
};

static bool testVtableInit(uiControl *c, void *implData, void *initData)
{
	return true;
}

static void testVtableFree(uiControl *c, void *implData)
{
	// do nothing
}

static void testVtableTestMethod(uiControl *c, void *implData)
{
	// do nothing
}

static void createTestVtable(uiControlVtable *vtable)
{
	memset(&vtable, 0, sizeof (uiControlVtable));
	vtable.Size = sizeof (uiControlVtable);
	vtable.Init = testVtableInit;
	vtable.Free = testVtableFree;
}

// TODO namePlaceholder == "name"
struct checkControlErrorsParams {
	const char *namePlaceholder;
	uiControlVtable *vtablePlaceholder;
	uiControlOSVtable *osVtablePlaceholder;
	size_t implDataSizePlaceholder;
	uiControlVtable *badSizeVtable;
};

testingTest(ControlErrors)
{
	uiControlVtable vtablePlacheolder, vtableBadSize;
	struct testOSVtable osVtablePlaceholder;

	// create valid vtables
	createTestVtables(&vtablePlaceholder, &osVtablePlaceholder);

	testProgrammerError(t, uiRegisterControlType(NULL, &vtablePlaceholder, &osVtablePlaceholder, sizeof (struct testImplData)),
		"invalid null pointer for name passed into uiRegisterControlType()");
	testProgrammerError(t, uiRegisterControlType("name", NULL, &osVtablePlaceholder, sizeof (struct testImplData)),
		"invalid null pointer for uiControlVtable passed into uiRegisterControlType()");
	memset(&vtableBadSize, 0, sizeof (uiEventOptions));
	vtableBadSize.Size = 1;
	testProgrammerError(t, uiRegisterControlType("name", &badVtableSize, &osVtablePlaceholder, sizeof (struct testImplData)),
		"wrong size 1 for uiControlVtable in uiRegisterControlType()");
#define testBadMethod(method) { \
	uiControlVtable bad ## method ## MethodVtable; \
	bad ## method ## MethodVtable = vtablePlaceholder; \
	bad ## method ## MehtodVtable.method = NULL; \
	testProgrammerError(t, uiRegisterControlType("name", &bad ## method ## MethodVtable, &osVtablePlaceholder, sizeof (struct testImplData)), \
		"TODO"); \
	}
	testProgrammerError(t, uiRegisterControlType("name", &vtablePlaceholder, NULL, sizeof (struct testImplData)),
		"invalid null pointer for uiControlOSVtable passed into uiRegisterControlType()");
	// OS vtable sizes are tested per-OS
}

#endif
