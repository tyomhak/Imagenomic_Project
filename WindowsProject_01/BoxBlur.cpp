#include "BoxBlur.h"



BoxBlur::BoxBlur(int radius)
	: GenericFilter(radius)
{
}


BoxBlur::~BoxBlur()
{
}

void BoxBlur::filter(Bitmap * out)
{
	GenericImage image(out);

	

}
