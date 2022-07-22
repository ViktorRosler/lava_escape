(TeX-add-style-hook
 "Kravspecifikation"
 (lambda ()
   (TeX-add-to-alist 'LaTeX-provided-package-options
                     '(("inputenc" "utf8") ("babel" "swedish") ("adjustbox" "export") ("ulem" "normalem") ("biblatex" "style=authoryear" "backend=biber")))
   (add-to-list 'LaTeX-verbatim-macros-with-braces-local "path")
   (add-to-list 'LaTeX-verbatim-macros-with-braces-local "url")
   (add-to-list 'LaTeX-verbatim-macros-with-delims-local "path")
   (add-to-list 'LaTeX-verbatim-macros-with-delims-local "url")
   (TeX-run-style-hooks
    "latex2e"
    "TDP005mall"
    "TDP005mall10"
    "inputenc"
    "babel"
    "adjustbox"
    "ulem"
    "tabularx"
    "caption"
    "biblatex"
    "csquotes")
   (TeX-add-symbols
    "version")
   (LaTeX-add-labels
    "tab:1"
    "tab:2"
    "fig:1"
    "tab:3"
    "fig:2"
    "tab:4"
    "fig:3"
    "tab:5"
    "fig:4"
    "fig:5"
    "fig:6"
    "section:1"
    "section:2"
    "section:3"
    "section:4"
    "section:5"
    "section:6"
    "section:7"
    "fig:7"
    "fig:8")
   (LaTeX-add-bibliographies
    "reference"))
 :latex)

