#include <iostream>
#include <string>
#include <stdexcept>
#include <unistd.h>
#include <cstdint>
#include <SFML/Graphics.hpp>
#include "Mandelbrot.hpp"
#include "Julia.hpp"
#include "Gradient.hpp"

#define G_VERSION 1
#define G_AUTHORS "Guillaume JORANDON"
#define G_DEFAULT_EXPORT_PATH "out.png"
#define G_DEFAULT_X 0
#define G_DEFAULT_Y 0
#define G_DEFAULT_PLOT 4
#define G_DEFAULT_MULTIPLICITY 2
#define G_DEFAULT_GAMMA 0.3
#define G_DEFAULT_ITERS 350
#define G_DEFAULT_W 1000
#define G_DEFAULT_H 1000
#define G_DEFAULT_U 0
#define G_DEFAULT_V 0

using namespace std;

void displayHelp(const string &name)
{
    cout << "Mandelbrot set computing v" << G_VERSION << " - " G_AUTHORS << endl << 
            "Usage: " << name << " [option(s)]" << endl <<
            " -h\t\tDisplay this current help and exits." << endl <<
            " -o PATH\tChange the output path (default: " << G_DEFAULT_EXPORT_PATH << ")." << endl <<
            " -g PATH\tSets a custom gradient. It should be a RGB(A) or greyscale PNG. Only the first line will be used." << endl <<
            " -x COORD\tSets a custom x center plot (default: " << G_DEFAULT_X << ")." << endl <<
            " -y COORD\tSets a custom y center plot (default: " << G_DEFAULT_Y << ")." << endl <<
            " -p SIZE\tSets a custom plot width (default: " << G_DEFAULT_PLOT << ")." << endl << 
            " -m REAL\tSets a custom multiplicity (default: " << G_DEFAULT_MULTIPLICITY << ")." << endl <<
            " -G REAL\tSets a custom gamma (default: " << G_DEFAULT_GAMMA << ")." << endl <<
            " -a\t\tDisables anti-aliased computing." << endl <<
            " -i INT\t\tSets the number of iterations (default: " << G_DEFAULT_ITERS << ")." << endl << 
            " -W INT\t\tSets the output width (default: " << G_DEFAULT_W << ")." << endl <<
            " -H INT\t\tSets the output height (default: " << G_DEFAULT_H << ")." << endl <<
            " -j\t\tCompute a julia set instead." << endl <<
            " -u REAL\tIf computing a julia set, defines the real part of c (default: " << G_DEFAULT_U << ")." << endl <<
            " -v REAL\tIf computing a julia set, defines the imaginary part of c (default: " << G_DEFAULT_V << ")." << endl;

}

using namespace TBDFRACTAL;

int main(int argc, char *argv[])
{
    string exportPath = G_DEFAULT_EXPORT_PATH;
    string gradientPath;
    vec2d center(G_DEFAULT_X, G_DEFAULT_Y);
    double plotWidth = G_DEFAULT_PLOT;
    double multiplicity = G_DEFAULT_MULTIPLICITY;
    double gamma = G_DEFAULT_GAMMA;
    bool antiAliasing = true;
    unsigned int iterations = G_DEFAULT_ITERS;
    vec2<size_t> size(G_DEFAULT_W, G_DEFAULT_H);
    bool julia = false;
    vec2d juliaC(G_DEFAULT_U, G_DEFAULT_V);

    int options;

    while((options = getopt(argc, argv, "ho:g:x:y:p:m:G:ai:W:H:ju:v:")) != -1)
        switch(options)
        {
            case 'h':
                displayHelp(argv[0]);
                exit(0);
            case 'o':
                exportPath = optarg;
                break;
            case 'g':
                gradientPath = optarg;
                break;
            case 'x':
                try
                {
                    center.x = stod(optarg);
                }
                catch(const invalid_argument &e)
                {
                    cerr << "Invalid -x argument." << endl;
                    cerr << "Try " << argv[0] << " -h for help." << endl;
                    exit(1);
                }
                break;
            case 'y':
                try
                {
                    center.y = stod(optarg);
                }
                catch(const invalid_argument &e)
                {
                    cerr << "Invalid -y argument." << endl;
                    cerr << "Try " << argv[0] << " -h for help." << endl;
                    exit(1);
                }
                break;
            case 'p':
                try
                {
                    plotWidth = stod(optarg);
                }
                catch(const invalid_argument &e)
                {
                    cerr << "Invalid -p argument." << endl;
                    cerr << "Try " << argv[0] << " -h for help." << endl;
                    exit(1);
                }
                break;
            case 'm':
                try
                {
                    multiplicity = stod(optarg);
                }
                catch(const invalid_argument &e)
                {
                    cerr << "Invalid -m argument." << endl;
                    cerr << "Try " << argv[0] << " -h for help." << endl;
                    exit(1);
                }
                break;
            case 'G':
                try
                {
                    gamma = stod(optarg);
                }
                catch(const invalid_argument &e)
                {
                    cerr << "Invalid -G argument." << endl;
                    cerr << "Try " << argv[0] << " -h for help." << endl;
                    exit(1);
                }
                break;
            case 'a':
                antiAliasing = false;
                break;
            case 'i':
                try
                {
                    int itersRel = stoi(optarg);
                    if(itersRel<0) iterations = -itersRel;
                    else iterations = itersRel;
                }
                catch(const invalid_argument &e)
                {
                    cerr << "Invalid -i argument." << endl;
                    cerr << "Try " << argv[0] << " -h for help." << endl;
                    exit(1);
                }
                break;
            case 'W':
                try
                {
                    int xRel = stoi(optarg);
                    if(xRel<0) size.x = -xRel;
                    else size.x = xRel;
                }
                catch(const invalid_argument &e)
                {
                    cerr << "Invalid -W argument." << endl;
                    cerr << "Try " << argv[0] << " -h for help." << endl;
                    exit(1);
                }
                break;
            case 'H':
                try
                {
                    int yRel = stoi(optarg);
                    if(yRel<0) size.y = -yRel;
                    else size.y = yRel;
                }
                catch(const invalid_argument &e)
                {
                    cerr << "Invalid -H argument." << endl;
                    cerr << "Try " << argv[0] << " -h for help." << endl;
                    exit(1);
                }
                break;
            case 'j':
                julia = true;
                break;
            case 'u':
                try
                {
                    juliaC.x = stod(optarg);
                }
                catch(const invalid_argument &e)
                {
                    cerr << "Invalid -u argument." << endl;
                    cerr << "Try " << argv[0] << " -h for help." << endl;
                    exit(1);
                }
                break;
            case 'v':
                try
                {
                    juliaC.y = stod(optarg);
                }
                catch(const invalid_argument &e)
                {
                    cerr << "Invalid -v argument." << endl;
                    cerr << "Try " << argv[0] << " -h for help." << endl;
                    exit(1);
                }
                break;
            default:
                cerr << "Try " << argv[0] << " -h for help." << endl;
                exit(1);
        }

    cout << "Set parameters:" << endl;
    if(julia)
    {
        cout << " * Julia set" << endl <<
                " * c = (" << juliaC.x << ", " << juliaC.y << ")" << endl;
    }
    else
    {
        cout << " * Mandelbrot set" << endl;
    }
    cout << " * size = (" << size.x << ", " << size.y << ")" << endl <<
            " * plot width = " << plotWidth << endl <<
            " * center = (" << center.x << ", " << center.y << ")" << endl <<
            " * multiplicity = " << multiplicity << endl <<
            "Computing parameters:" << endl <<
            " * iterations = " << iterations << endl <<
            " * antiAliasing = " << (antiAliasing?"true":"false") << endl <<
            "Rendering parameters:" << endl <<
            " * gamma = " << gamma << endl <<
            " * gradian = " << (gradientPath.size()==0?"[default]":gradientPath) << endl <<
            " * output = " << exportPath << endl;
  
    cout << endl;

    Gradient grad;
    if(gradientPath.size() == 0)
        grad.create();
    else
        grad.loadFromFile(gradientPath);

    Mandelbrot *set = NULL;

    if(julia)
    {
        set = new Julia(plotWidth, center, size);
        static_cast<Julia*>(set)->c(juliaC);
    }
    else
    {
        set = new Mandelbrot(plotWidth, center, size);
    }

    set->useLogHorizon(antiAliasing);
    set->multiplicity(multiplicity);

    cout << "Computing..." << endl;
    set->compute(iterations);
    cout << "Rendering..." << endl;
    sf::Image output = set->render(gamma, grad);
    cout << "Saving..." << endl;
    output.saveToFile(exportPath);

    delete set;

    return 0;
}
