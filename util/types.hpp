#ifndef TYPES_H
#define TYPES_H


namespace util
{
	/**
	 * identity
	 */
	template<class T>
	struct identity
	{
		typedef T type;
	};

	/**
	 * index
	 */
	template<size_t... vals>
	struct index
	{
	};

}//end namespace util


#endif
