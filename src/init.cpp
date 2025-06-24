#include <bluec/bluec.h>
#include "utils/utils.h"
#include "libctx.h"

namespace BlueC
{

static BlueCErrorCodes __Init()
{
	allocCTX();
	return BLUEC_ERROR_NONE;
}

static BlueCErrorCodes __DeInit()
{
	deallocCTX();
	return BLUEC_ERROR_NONE;
}

} // namespace BlueC


BlueCErrorCodes bluec_Init()
{
	MAKE_INTERNAL_CALL(BlueC::__Init());
}

BlueCErrorCodes bluec_DeInit()
{
	MAKE_INTERNAL_CALL(BlueC::__DeInit());
}