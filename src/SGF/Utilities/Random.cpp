#include <ctime>
#include "Random.h"

SGF_NAMESPACE(::Util)

Random Random::s_Ran;

Random& Random::get()
{
	return s_Ran;
}

void Random::init()
{
	Random r;
	r.setupStatic();
}

Random::Random()
{
	m_Engine.seed((unsigned)std::time(nullptr));
}

Random::Random(unsigned int seed)
{
	m_Engine.seed(seed);
}

	
void Random::setupStatic()
{
	s_Ran = Random();
}
	
END_NAMESPACE
