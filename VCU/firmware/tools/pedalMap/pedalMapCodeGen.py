import argparse, glob, jinja2, os
import matplotlib.pyplot as plt
from math import factorial

this_dir = os.path.dirname(__file__)
target_dir = os.path.abspath(os.path.join(this_dir, "..", "..", "app", "generated"))
# template_file = glob.glob("*.jinja", root_dir=this_dir)[0]
template_file = [file for file in os.listdir(this_dir) if file.endswith(".jinja")][0]

DEFAULT_EXPONENT = 1.3
DEFAULT_POINT = 0.5
DEFAULT_ORDER = 6


"""
The pedal map should translate a raw pedal poisition to a "mapped" pedal position for the sake of
smoothing/variable sensitibity throughout the pedal range.
Having the pedal position represented as a fraction (0.0 to 1.0) mean that this map can be
implemented as a power function x^p with p > 0.
Non-integer exponents aren't native operations, but can be well approximated with via Taylor series.
"""

#---------------------------------------------------------------------------------------------------
# Helper functions
#---------------------------------------------------------------------------------------------------
def Render(coeffs, p=DEFAULT_EXPONENT, a=DEFAULT_POINT):
    configDict = {
        "p": p,
        "a": a,
        "N": len(coeffs) - 1,
        "coeffs": coeffs,
    }

    output_path = os.path.abspath(os.path.join(target_dir, template_file[:-6])) # remove .jinja suffix
    output_file = open(output_path, 'w')
    env = jinja2.Environment(loader=jinja2.FileSystemLoader(searchpath=this_dir), extensions=['jinja2.ext.do', 'jinja2.ext.loopcontrols'])
    env.trim_blocks = True
    env.lstrip_blocks = True
    env.keep_trailing_newline = True
    output_file.write(env.get_template(template_file).render(configDict))
    output_file.close()


# p = exponent for power function
# a = point of approximation for Taylor series
# n = order of Taylor series
# f(x) = x^p
# f'(x) = p * x^(p-1)
def GenerateTaylorSeries(p=DEFAULT_EXPONENT, a=DEFAULT_POINT, n=DEFAULT_ORDER):
    coeffs = []
    C = 1
    P = p
    for i in range(n+1):
        coeff = (C * pow(a, P)) / factorial(i)
        coeffs += [coeff]
        C *= P
        P -= 1
    return coeffs


def VisualizeTaylorSeries(coeffs, p=DEFAULT_EXPONENT, a=DEFAULT_POINT):
    x_arr = [i / 100.0 for i in range(101)]
    y = [pow(x, p) for x in x_arr]
    y_approx = [sum([coeff * pow((x-a), n) for n, coeff in enumerate(coeffs)]) for x in x_arr]
    N = len(coeffs) - 1

    plt.plot(x_arr, x_arr, linestyle="dashed")
    plt.plot(a, pow(a, p), marker='*')
    plt.plot(x_arr, y, label="Power function")
    plt.plot(x_arr, y_approx, label="Taylor series")
    plt.legend()
    plt.title(f"N={N} Taylor series approximation of x^{p}")
    plt.xlabel("raw")
    plt.ylabel("mapped")
    plt.show()


#---------------------------------------------------------------------------------------------------
# Parse and run
#---------------------------------------------------------------------------------------------------
def get_args():
    parser = argparse.ArgumentParser()
    parser.add_argument("--p", dest="p", help="Exponent for power function", default=DEFAULT_EXPONENT, type=float)
    parser.add_argument("--n", dest="n", help="Order for Taylor series", default=DEFAULT_ORDER, type=int)
    parser.add_argument("--a", dest="a", help="Point of approximation for Taylor series", default=DEFAULT_POINT, type=float)

    return parser.parse_args()


if __name__ == "__main__":
    args = get_args()
    print("Generating pedal map code for VCU")
    coeffs = GenerateTaylorSeries(p=args.p, a=args.a, n=args.n)
    VisualizeTaylorSeries(coeffs, p=args.p, a=args.a)
    Render(coeffs, p=args.p, a=args.a)
