\LoadClass{article}
\usepackage{xeCJK}
\usepackage{ctex}
\usepackage{graphicx}
\usepackage{geometry}
\usepackage{titlesec}
\usepackage{titletoc}
\usepackage{fancyhdr}
\usepackage{enumitem}
\usepackage{listings}
\usepackage{xcolor}
\usepackage{amsmath}
\usepackage{amssymb}
\usepackage{multirow}
\usepackage{bigstrut}
\usepackage{float}

\linespread{1.2}
\geometry{top=1in,bottom=1in,left=1in,right=1in}
\setcounter{secnumdepth}{2}
\renewcommand\thesection{\chinese{section}、}
\renewcommand\thesubsection{\arabic{subsection}.}
\renewcommand\thesubsubsection{\Roman{subsubsection}}
\newlist{clause}{enumerate}{1}
\setlist[clause]{fullwidth,itemindent=2em,label=(\arabic*)}
\newCJKfontfamily[song]\song{SimSun}[AutoFakeBold]

%目录设置
\renewcommand{\contentsname}{\centerline{\Large 目\quad 录}}
\setcounter{tocdepth}{2}
\titlecontents{section}
              [3cm]
              {\bf \large}%
              {\contentslabel{2.5em}}%
              {}%
              {\titlerule*[0.5pc]{$\cdot$}\contentspage\hspace*{3cm}}%
\titlecontents{subsection}
              [4cm]
              {\normalsize}%
              {\contentslabel{2.5em}}%
              {}%
              {\titlerule*[0.5pc]{$\cdot$}\contentspage\hspace*{3cm}}%

% \setmainfont{CMU Serif}
\setmonofont{Lucida Console}
\setsansfont{SimHei}
\titleformat*{\section}{\large\bfseries}
\titleformat*{\subsection}{\normalsize\bfseries}
\titleformat*{\subsubsection}{\normalsize\bfseries}
\graphicspath{{figures/}{figure/}{pictures/}%
{picture/}{pic/}{pics/}{image/}{images/}}

\titlespacing{\subsection}{2em}{*4}{*1.5}
\titlespacing{\subsubsection}{2em}{*4}{*1.5}

\definecolor{dkgreen}{rgb}{0,0.6,0}
\definecolor{gray}{rgb}{0.5,0.5,0.5}
\definecolor{comment}{rgb}{0.56,0.64,0.68}

\lstset{
  frame=tb,
  aboveskip=3mm,
  belowskip=3mm,
  xleftmargin=2em,
  xrightmargin=2em,
  showstringspaces=false,
  columns=flexible,
  framerule=1pt,
  rulecolor=\color{gray!35},
  backgroundcolor=\color{gray!5},
  basicstyle={\small\ttfamily},
  numbers=none,
  numberstyle=\tiny\color{gray},
  keywordstyle=\color{blue},
  commentstyle=\color{comment},
  stringstyle=\color{dkgreen},
  breaklines=true,
  breakatwhitespace=true,
  tabsize=2,
}

\pagestyle{fancy}
\lhead{实验名称：\newtitle}
\chead{姓名：\name}
\rhead{学号：\stuid}
