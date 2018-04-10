#ifndef _MANDELBROT_MANDELBROT_HPP_
#define _MANDELBROT_MANDELBROT_HPP_

#include "RGBBitmap.hpp"
#include "RGBGradient.hpp"
#include <cstdint>
#include <complex>
#include <cmath>

template <typename T>
struct vec2
{
	T x,
	  y;

	vec2(T xx, T yy): x(xx), y(yy) {}
};

typedef vec2<double> vec2d;

class Mandelbrot
{
public:

	/*! \brief Empty constructor.
	 *
	 *  Builds a set with the following parameters: 
	 *  * size : 500*500px
	 *  * plotWidth : 4 (the entire mandelbrot set fits into a circle of radius r=2)
	 *  * center : (0;0)
	 *  * multiplicity : 2
	 */
	Mandelbrot();
	/*! \brief Default constructor.
	 *  \param resSize Size of the final image.
	 *  \param plotWidth Width of the cartesian coordinate system.
	 *  \param center Center of the image relative to the cartesian coordinate system.
	 */
	Mandelbrot(vec2<size_t> resSize, double plotWidth, vec2d center, double multiplicity);
	/*! \brief Destructor.
	 */
	~Mandelbrot();
	/*! \brief Computes the Mandelbrot set.
	 *  \param maxIterations Maximum number of iterations per pixel.
	 *  \param gamma Gamma for the rendering.
	 *  \param antiAliasing If true, will use a different method to get smooth gradient instead of segmented one.
	 *  \param julia If true, will compute a Julia set instead.
	 *  \param juliaC If julia is true, it corresponds to the c value.
	 */
	void compute(unsigned int maxIterations, bool antiAliasing, bool julia, vec2d juliaC);
	/*! \brief Renders the final image based on computing result. Mandelbrot::compute must have been called at least once!
	 *  \param gamma Gamma for the rendering.
	 *  \param gradient The gradient to use.
	 */
	void render(double gamma, RGBGradient &gradient);
	/*! \brief Accessor of m_pixels. Use it to access to the rendered image and, say, export it.
	 *  \return A reference to m_pixels.
	 */
	RGBBitmap &getResult();
	
private:
	
	RGBBitmap m_pixels; //!< Result of the rendering.
	double *m_result; //!< Result of the computing.
	double m_xmin, //!< Abscissa of the beginning of the image (left upper point).
		   m_ymin; //!< Ordinate of the beginning of the image (left upper point).
	double m_dIt; //!< Increment for both abscissa and ordinate.
	double m_multiplicity;
};

#endif //_MANDELBROT_MANDELBROT_HPP_
