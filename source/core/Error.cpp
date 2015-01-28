#include "core/Error.h"
#include "core/Debug.h"

using namespace ice;
using namespace core;

//Make sure these are defined in the same order as the ERROR_CODE enum
const char* g_errorMessages[] = 
{
	"Out of memory."
};

Error::Error(ERROR_CODE errorCode)
	:m_errorCode(errorCode)
{
	
}

ERROR_CODE Error::getCode()
{
	return m_errorCode;
}

const char* Error::getMessage()
{
	return g_errorMessages[m_errorCode];
}

void Error::print()
{
	Debug::log(LL_ERROR, getMessage());
}