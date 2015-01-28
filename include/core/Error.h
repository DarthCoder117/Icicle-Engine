#ifndef ERROR_H
#define ERROR_H

namespace ice
{
	namespace core
	{
		enum ERROR_CODE
		{
			EC_OUT_OF_MEMORY
		};

		class Error
		{
		public:

			Error(ERROR_CODE errorCode);

			ERROR_CODE getCode();

			const char* getMessage();

			void print();

		private:

			ERROR_CODE m_errorCode;
		};
	}
}

#endif