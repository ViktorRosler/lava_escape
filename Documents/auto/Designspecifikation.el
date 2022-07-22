(TeX-add-style-hook
 "Designspecifikation"
 (lambda ()
   (TeX-add-to-alist 'LaTeX-provided-package-options
                     '(("inputenc" "utf8") ("babel" "swedish") ("adjustbox" "export") ("biblatex" "style=authoryear" "backend=biber")))
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
    "tabularx"
    "caption"
    "biblatex"
    "csquotes")
   (TeX-add-symbols
    "version")
   (LaTeX-add-labels
    "fig:1")
   (LaTeX-add-bibliographies
    "reference"))
 :latex)

