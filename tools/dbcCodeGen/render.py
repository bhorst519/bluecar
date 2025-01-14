import jinja2, os, string

this_dir = os.path.dirname(__file__)

template_files = [
    "ALIAS_messageInfo.hpp.jinja",
    "ALIAS_canTransmitter.hpp.jinja",
    "ALIAS_canTransmitter.cpp.jinja",
    "ALIAS_canReceiver.hpp.jinja",
    "ALIAS_canReceiver.cpp.jinja",
    "ALIAS_canReceiverHook.h.jinja",
]

def evalKeys(expression, keys):
    return eval(string.Template(expression).substitute(keys))

def Render(targetDir, alias, configDict):
    for jinja_file in template_files:
        output_path = os.path.abspath(os.path.join(targetDir, jinja_file[:-6].replace("ALIAS", alias))) # remove .jinja suffix
        output_file = open(output_path, 'w')
        env = jinja2.Environment(loader=jinja2.FileSystemLoader(searchpath=this_dir), extensions=['jinja2.ext.do', 'jinja2.ext.loopcontrols'])
        env.filters["max"] = max
        env.filters["min"] = min
        env.filters["evalKeys"] = evalKeys
        env.trim_blocks = True
        env.lstrip_blocks = True
        env.keep_trailing_newline = True
        output_file.write(env.get_template(jinja_file).render(configDict))
        output_file.close()
