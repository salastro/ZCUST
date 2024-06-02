\NeedsTeXFormat{LaTeX2e}
\ProvidesClass{zc-ust-hw}[2023/11/13 LaTeX class for Zewail City University of Science and Technology assignments]

\LoadClass[12pt, a4paper]{article}

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

\RequirePackage{xcolor}
\colorlet{backcolour}{gray!10!white}
\colorlet{commentcolour}{green!40!black}
\colorlet{keywordcolour}{blue}
\colorlet{stringcolour}{orange!80!white}
\colorlet{rulecolour}{black}

%%%%%%%%%%
%  Code  %
%%%%%%%%%%

% \RequirePackage{listings}
% \lstdefinestyle{mystyle}{
%   backgroundcolor=\color{backcolour},
%   basicstyle=\ttfamily\small,
%   breakatwhitespace=false,
%   breaklines=true,
%   captionpos=b,
%   frame=single,
%   commentstyle=\color{commentcolour},
%   escapeinside={\%*}{*)},
%   keywordstyle=\color{keywordcolour},
%   numbers=left,
%   numbersep=5pt,
%   numberstyle=\tiny\color{gray},
%   rulecolor=\color{rulecolour},
%   showspaces=false,
%   showstringspaces=false,
%   showtabs=false,
%   stepnumber=1,
%   stringstyle=\color{stringcolour},
%   tabsize=4,
% }
% \lstset{style=mystyle}

\RequirePackage[outputdir=./output/]{minted}

\setminted{
  frame=single,
  bgcolor=gray!10!white,
  linenos,
  breaklines,
}

%%%%%%%%%%%%%%
%  Packages  %
%%%%%%%%%%%%%%

\RequirePackage{amsmath,amsfonts,mathtools,amsthm,amssymb,bm, mathrsfs} % Math.
\RequirePackage{caption} % Captions.
\RequirePackage{enumitem} % Lists.
\RequirePackage{float} % Floats.
\RequirePackage{graphicx} % Images and graphics.
\RequirePackage{hyperref} % Links.
\RequirePackage{pdfpages} % PDF.
\RequirePackage{subcaption} % Subcaptions.
\RequirePackage{wrapfig} % Wrap text around figures.

%%%%%%%%%%%%%%
%  PGFplots  %
%%%%%%%%%%%%%%

\RequirePackage{pgfplots}
\pgfplotsset{compat=1.17}
\pgfplotsset{
  axis x line=middle,
  axis y line=middle,
  axis line style={<->},
  xlabel={$x$},
  ylabel={$y$},
  % grid=both,
}

%%%%%%%%%%
%  TikZ  %
%%%%%%%%%%

\RequirePackage[framemethod=TikZ]{mdframed}
\RequirePackage{tikz}
\RequirePackage{tikz-cd}
\RequirePackage{tikzsymbols}

\usetikzlibrary{intersections, angles, quotes, calc, positioning}
\usetikzlibrary{arrows.meta}
\usetikzlibrary{calc, shapes.geometric}

\RequirePackage[american]{circuitikz}

%%%%%%%%%%%%%%%%%%
%  Environments  %
%%%%%%%%%%%%%%%%%%

% Solution environment
\newenvironment{sol}
{
  \renewcommand\qedsymbol{$\blacksquare$}
  \begin{proof}[Solution]} {\end{proof}
}

%%%%%%%%%%%%%%
%  InkScape  %
%%%%%%%%%%%%%%

\RequirePackage{import}
\RequirePackage{xifthen}
\RequirePackage{pdfpages}
\newcommand{\incfig}[1]{%
  \def\svgwidth{\columnwidth}
  \import{./figures/}{#1.pdf_tex}
}

%%%%%%%%%%
%  Sets  %
%%%%%%%%%%

\newcommand{\R}{\mathbb{R}}
\newcommand{\N}{\mathbb{N}}
\newcommand{\Z}{\mathcal{Z}}
\newcommand{\C}{\mathbb{C}}
\newcommand{\Q}{\mathbb{Q}}

%%%%%%%%%%%
%  Title  %
%%%%%%%%%%%

% Define the variables
\newcommand{\project}[1]{\gdef\@project{#1}}
\newcommand{\course}[1]{\gdef\@course{#1}}
\newcommand{\semester}[1]{\gdef\@semester{#1}}
\newcommand{\team}[1]{\gdef\@team{#1}}

% Redefine the maketitle command
\renewcommand{\maketitle}{
  \begin{flushleft}
    ZC - University of Science and Technology \\
    \@course \\
    \@semester
  \end{flushleft}

  \begin{flushright}\vspace{-15mm}
    \vspace{-0.75cm}
    \includegraphics[height=2cm]{logo.jpg}
  \end{flushright}

  \begin{center}
    \vspace{-0.5cm}
    \Huge \@project\\
  \end{center}

  \begin{flushleft}
    \ifx\@team\empty\else
      Team Name: \textbf{\@team} \\
    \fi
    Team Members: \\

    \begin{tabular}{ccc}
      \textbf{202200341} & \textbf{Abdulrahman Magdy} & \textbf{\href{mailto:s-abdulrahman.abdulrahman@zewailcity.edu.eg}{s-abdulrahman.abdulrahman@zewailcity.edu.eg}} \\
      \textbf{202200393} & \textbf{Ahmed Amgad} & \textbf{\href{mailto:s-ahmed-ali@zewailcity.edu.eg}{s-ahmed-ali@zewailcity.edu.eg}} \\
      \textbf{202200282} & \textbf{Khaled Mahmoud} & \textbf{\href{mailto:s-khaled.eldadr@zewailcity.edu.eg}{s-khaled.eldadr@zewailcity.edu.eg}} \\
      \textbf{202201079} & \textbf{SalahDin Rezk} & \textbf{\href{mailto:s-salahdin.rezk@zewailcity.edu.eg}{s-salahdin.rezk@zewailcity.edu.eg}} \\
    \end{tabular}  \\
  \end{flushleft}

  \rule{0.95\linewidth}{0.1mm}

  \bigskip
}

% Set default values for the variables
\gdef\@project{}
\gdef\@course{}
\gdef\@semester{}
\gdef\@team{}

\endinput
