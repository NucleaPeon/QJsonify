<!-- Improved compatibility of back to top link: See: https://github.com/othneildrew/Best-README-Template/pull/73 -->
<a name="readme-top"></a>
<!--
*** Thanks for checking out the Best-README-Template. If you have a suggestion
*** that would make this better, please fork the repo and create a pull request
*** or simply open an issue with the tag "enhancement".
*** Don't forget to give the project a star!
*** Thanks again! Now go create something AMAZING! :D
*** Will do.
-->


<!-- PROJECT LOGO -->
<br />
<div align="center">
  <a href="https://github.com/NucleaPeon/QJsonify">
    <img src="icons/qjsonify-512x512.png" alt="Logo" width="80" height="80">
  </a>

  <h3 align="center">QJsonify</h3>

  <p align="center">
    Prettify and Minify your JSON files locally. Don't give out your precious information to online sources.
    <br />
    <br />
    <a href="https://github.com/NucleaPeon/QJsonify/issues">Report Bug</a>
    ·
    <a href="https://github.com/NucleaPeon/QJsonify/issues">Request Feature</a>
  </p>
</div>



<!-- TABLE OF CONTENTS -->
<details>
  <summary>Table of Contents</summary>
  <ol>
    <li>
      <a href="#about-the-project">About The Project</a>
      <ul>
        <li><a href="#built-with">Built With</a></li>
      </ul>
    </li>
    <li>
      <a href="#getting-started">Getting Started</a>
      <ul>
        <li><a href="#prerequisites">Prerequisites</a></li>
        <li><a href="#installation">Installation</a></li>
      </ul>
    </li>
    <li><a href="#usage">Usage</a></li>
    <li><a href="#roadmap">Roadmap</a></li>
    <li><a href="#contributing">Contributing</a></li>
    <li><a href="#license">License</a></li>
    <li><a href="#contact">Contact</a></li>
  </ol>
</details>



<!-- ABOUT THE PROJECT -->
## About The Project

[![QJsonify on Linux][product-screenshot-linux]](https://github.com/NucleaPeon/QJsonify)
[![QJsonify on OS X Snow Leopard][product-screenshot-osx]](https://github.com/NucleaPeon/QJsonify)
[![QJsonify on Windows 7][product-screenshot-win7]](https://github.com/NucleaPeon/QJsonify)

_A Windows XP and 7 version are planned._

QJsonify is a project that aims to help developers keep their data local. There are many great online JSON minifiers and prettifiers, but all that functionality is easily accessible within the Qt5 Framework and this avoids submitting data across the network.

It's faster and more secure, you can toggle quickly between minified and prettified forms as well as print and export said json files in a couple clicks.

This project includes Oxygen Icons <a href="https://techbase.kde.org/Projects/Oxygen/Licensing">https://techbase.kde.org/Projects/Oxygen/Licensing</a> which are licensed under the LGPL v3 (see LICENSE-LGPL3 file). All files under this license are located in the ``icons/`` directory except jsonify-* files which I created for the program logo. These also can be licensed under the LGPL v3.

The oxygen repo is old when checked out, some svg/svgz files may not be available for inclusion with the project. Latest commit is ``bff159d338fe08be09146a5ee17b9b6efa8a2c8d``. See https://github.com/KDE/oxygen-icons for latest repo commits.

Files not included:

* format-line-spacing-normal.svg*
* format-line-spacing-triple.svg*


<p align="right">(<a href="#readme-top">back to top</a>)</p>

### Built With

This project is built on a minimum Qt5 version of Qt 5.3.2. For OS X 10.6.8, you can download the Qt5 binary at my <a href="https://github.com/NucleaPeon/qt5-sle/releases/tag/v5.3.2">other repository</a>.

It is also tested using Qt5.15 on Linux amd64.

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- GETTING STARTED -->
## Getting Started

Clone the repo:

```sh
    git clone https://github.com/NucleaPeon/QJsonify.git
```

### Prerequisites

You will need:
* git
* clang >= 3 OR g++ >= 4.2
* make
* Qt5 >= 5.3.2


### Installation

* For linux:

    ```sh
    cd QJsonify
    qmake -r
    make
    make install
    ```

* For Mac:

    ```sh
    cd QJsonify
    qmake -r
    make
    ```

    Then drag and drop the resulting QJsonify.app/ folder into your Applications folder.

I recommend calling ``make`` with the option ``-jN`` where ``N`` is the number of cores of your cpu.

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- USAGE EXAMPLES -->
## Usage

* Use the ``Open`` action to load your ``.json`` file.
* Select Minify or Prettify
* Print or Export the output to file.

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- ROADMAP -->
## Roadmap

- [ ] Remote file read and write
- [ ] Compile for, and add Windows 7 binary
- [ ] Implement Recent Files menu and have ability to clear it
- [ ] Use CMake as the build system instead of qmake
- [ ] Create a debian release package
- [ ] Show statistics between prettified and minified file sizes
- [ ] Have an editor button to allow system editor to edit json file

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- CONTRIBUTING -->
## Contributing

Contributions are what make the open source community such an amazing place to learn, inspire, and create. Any contributions you make are **greatly appreciated**.

Please remember to avoid any c++11 code and any Qt 5.4.0+ introduced functions for ``Q_OS_MAC`` def blocks as this project must be compatible with Snow Leopard (OS X 10.6.8).

If you have a suggestion that would make this better, either create an issue with your idea(s) or fork the repo and create a pull request.

Don't forget to give the project a star! Thanks again!

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- LICENSE -->
## License

Distributed under the GPL v3.0 License. See `LICENSE` for more information.

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- CONTACT -->
## Contact

You can email me at <initial.dann@gmail.com>.

[https://github.com/NucleaPeon](https://github.com/NucleaPeon)

Thanks to the <a href="https://github.com/othneildrew/Best-README-Template">https://github.com/othneildrew/Best-README-Template</a> project for helping me get started on this README.md.

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- MARKDOWN LINKS & IMAGES -->
<!-- https://www.markdownguide.org/basic-syntax/#reference-style-links -->
[product-screenshot-linux]: images/qjsonify-linux.png
[product-screenshot-osx]: images/qjsonify-osx.png
[product-screenshot-win7]: images/qjsonify-win7.png
