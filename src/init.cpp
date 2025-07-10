#include <bluec/bluec.h>
#include "utils/utils.h"
#include "libctx.h"

namespace BlueC
{

static BlueCErrorCodes __Init(bool runMainLoop)
{
	allocCTX(runMainLoop);
	return BLUEC_ERROR_NONE;
}

static BlueCErrorCodes __DeInit()
{
	deallocCTX();
	return BLUEC_ERROR_NONE;
}

} // namespace BlueC


BlueCErrorCodes bluec_Init(bool runMainLoop)
{
	MAKE_INTERNAL_CALL(BlueC::__Init(runMainLoop));
}

BlueCErrorCodes bluec_DeInit()
{
	MAKE_INTERNAL_CALL(BlueC::__DeInit());
}