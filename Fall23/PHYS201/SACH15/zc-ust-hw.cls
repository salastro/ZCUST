\NeedsTeXFormat{LaTeX2e}
\ProvidesClass{zc-ust-hw}[2022/11/01 LaTeX class for Zewail City Universt of Science and Technology assignments]

\LoadClass[11pt, letterpaper]{article}

%%%%%%%%%%%%%%
%  Geometry  %
%%%%%%%%%%%%%%

\setlength{\textwidth}{6.5in}
\setlength{\textheight}{9.in}
\setlength{\oddsidemargin}{0in}
\setlength{\headheight}{0in}

\RequirePackage[margin=2cm]{geometry}

%%%%%%%%%%%%
%  Colors  %
%%%%%%%%%%%%

\RequirePackage{color}
\definecolor{codegreen}{rgb}{0,0.6,0}
\definecolor{codegray}{rgb}{0.5,0.5,0.5}
\definecolor{codepurple}{rgb}{0.58,0,0.82}
\definecolor{backcolour}{rgb}{0.95,0.95,0.92}

%%%%%%%%%%%
%  Lists  %
%%%%%%%%%%%

\RequirePackage{listings}
\lstdefinestyle{mystyle}{
    backgroundcolor=\color{backcolour},
    commentstyle=\color{codegreen},
    keywordstyle=\color{magenta},
    numberstyle=\tiny\color{codegray},
    stringstyle=\color{codepurple},
    basicstyle=\footnotesize,
    breakatwhitespace=false,
    breaklines=true,
    captionpos=b,
    keepspaces=true,
    numbers=left,
    numbersep=5pt,
    showspaces=false,
    showstringspaces=false,
    showtabs=false,
    tabsize=2
}
\lstset{style=mystyle}

%%%%%%%%%%%%%%
%  Packages  %
%%%%%%%%%%%%%%

\RequirePackage{hyperref} % Links.
\RequirePackage{amsmath,amsfonts,mathtools,amsthm,amssymb,bm} % Math.
\RequirePackage{graphicx} % Images and graphics.
\RequirePackage{pdfpages} % PDF.

%%%%%%%%%%%%%%
%  PGFplots  %
%%%%%%%%%%%%%%

\RequirePackage{pgfplots}
\pgfplotsset{compat=1.13}

%%%%%%%%%%
%  TikZ  %
%%%%%%%%%%

\RequirePackage[framemethod=TikZ]{mdframed}
\RequirePackage{tikz}
\RequirePackage{tikz-cd}
\RequirePackage{tikzsymbols}

\usetikzlibrary{intersections, angles, quotes, calc, positioning}
\usetikzlibrary{arrows.meta}

%%%%%%%%%%%
%  Title  %
%%%%%%%%%%%

\renewcommand\maketitle{
    \begin{flushleft}
        Student Name: \name \\
        Student ID: \id \\
        Date: \today
    \end{flushleft}

    \begin{flushright}\vspace{-15mm}
        \includegraphics[height=2cm]{logo.jpg}
    \end{flushright}

    \begin{center}\vspace{-1cm}
        \textbf{\large \course}\\
        \assignment
    \end{center}

    \rule{\linewidth}{0.1mm}

    \bigskip
    \bigskip
}
