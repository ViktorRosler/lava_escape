(TeX-add-style-hook
 "TDP005-mall"
 (lambda ()
   (TeX-add-to-alist 'LaTeX-provided-package-options
                     '(("inputenc" "utf8") ("babel" "swedish")))
   (TeX-run-style-hooks
    "latex2e"
    "TDP005mall"
    "TDP005mall10"
    "inputenc"
    "babel")
   (TeX-add-symbols
    "version"))
 :latex)

