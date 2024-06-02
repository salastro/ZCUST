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

\RequirePackage{listings}
\lstdefinestyle{mystyle}{
  backgroundcolor=\color{backcolour},
  basicstyle=\ttfamily\small,
  breakatwhitespace=false,
  breaklines=true,
  captionpos=b,
  frame=single,
  commentstyle=\color{commentcolour},
  escapeinside={\%*}{*)},
  keywordstyle=\color{keywordcolour},
  numbers=left,
  numbersep=5pt,
  numberstyle=\tiny\color{gray},
  rulecolor=\color{rulecolour},
  showspaces=false,
  showstringspaces=false,
  showtabs=false,
  stepnumber=1,
  stringstyle=\color{stringcolour},
  tabsize=4,
}
\lstset{style=mystyle}

%%%%%%%%%%%%%%
%  Packages  %
%%%%%%%%%%%%%%

\RequirePackage{amsmath,amsfonts,mathtools,amsthm,amssymb,bm} % Math.
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

%%%%%%%%%%%
%  Title  %
%%%%%%%%%%%

% Define the variables
\newcommand{\name}[1]{\gdef\@name{#1}}
\newcommand{\id}[1]{\gdef\@id{#1}}
\newcommand{\course}[1]{\gdef\@course{#1}}
\newcommand{\assignment}[1]{\gdef\@assignment{#1}}

% Redefine the maketitle command
\renewcommand{\maketitle}{
  \begin{flushleft}
    \ifx\@name\empty\else
      Name: \@name \\
    \fi
    \ifx\@id\empty\else
      ID: \@id \\
    \fi
    Date: \today
  \end{flushleft}

  \begin{flushright}\vspace{-15mm}
    \includegraphics[height=2cm]{logo.jpg}
  \end{flushright}

  \begin{center}
    \vspace{-1cm}
    \textbf{\large \@course}\\
    \@assignment
  \end{center}

  \rule{0.95\linewidth}{0.1mm}

  \bigskip
  \bigskip
}

% Set default values for the variables
\gdef\@name{}
\gdef\@id{}
\gdef\@course{}
\gdef\@assignment{}

\endinput
