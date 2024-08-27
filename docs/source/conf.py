# Configuration file for the Sphinx documentation builder.
#

project = 'libutils'
copyright = '2024, Paweł Maciocha'
author = 'Paweł Maciocha'
release = '1.0.0'

# -- General configuration ---------------------------------------------------

import subprocess
subprocess.call('doxygen Doxyfile.in', shell=True)

# -----------------------------------------------------------------------------

extensions = [
    'sphinx.ext.autodoc',
    'sphinx.ext.intersphinx',
    'sphinx.ext.autosectionlabel',
    'sphinx.ext.todo',
    'sphinx.ext.coverage',
    'sphinx.ext.mathjax',
    'sphinx.ext.ifconfig',
    'sphinx.ext.viewcode',
    'sphinx.ext.inheritance_diagram',
    'breathe'
]

suppress_warnings = ['autosectionlabel.*']

templates_path = ['_templates']
exclude_patterns = ['_build', 'Thumbs.db', '.DS_Store']
highlight_language = 'c++'

cpp_index_common_prefix = ['libutils::']

# -- Options for HTML output -------------------------------------------------

html_theme = 'furo'
html_theme_options = {
    "dark_css_variables": {
        "color-background-hover--transparent": "#202020",
    },
}

html_title = 'libutils'

html_static_path = ['_static']

breathe_projects = {
    "libutils": "../build/xml/"
}
