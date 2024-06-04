#!/usr/bin/env python3

import os 

cwd = os.getcwd()
doxygen_xml_output_dir = cwd + '/_build/xml'
os.chdir(doxygen_xml_output_dir)
group_files = [f for f in os.listdir() if (os.path.isfile(f)
                                           and str(f).startswith('group__')
                                           and str(f).endswith('.xml'))]
group_dirs = [d.replace('.xml', '') for d in group_files]

for directory in group_dirs:
    try: 
        os.mkdir(directory)
    except FileExistsError:
        pass

for (file, directory) in zip(group_files, group_dirs):
    os.replace(doxygen_xml_output_dir + '/' + file, 
               doxygen_xml_output_dir + '/' + directory + '/' + file) 

