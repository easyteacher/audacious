/*
 * dark-theme.cc
 * Copyright 2021 John Lindgren
 *
 * Based on the author's previous work:
 * https://github.com/jlindgren90/old-style-theme
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions, and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions, and the following disclaimer in the documentation
 *    provided with the distribution.
 *
 * This software is provided "as is" and without any warranty, express or
 * implied. In no event shall the authors be liable for any damages arising from
 * the use of this software.
 */

#include "libaudqt.h"
#include "libaudqt-internal.h"

#include <QApplication>
#include <QPalette>
#include <QProxyStyle>
#include <QStyle>
#include <QStyleFactory>

namespace audqt {

static const char * dark_css =
    "QToolTip {\n"
    "  color: palette(text);\n"
    "  background: #1d2c3f;\n"
    "  border: 1px solid palette(highlight);\n"
    "}\n"
    "\n"
    "QMenuBar, QToolBar {\n"
    "  border: none;\n"
    "}\n"
    "\n"
    "QMenuBar {\n"
    "  spacing: 0;\n"
    "}\n"
    "\n"
    "QMenuBar::item {\n"
    "  background: transparent;\n"
    "  padding-left: 6px;\n"
    "  padding-right: 6px;\n"
    "  padding-top: 2px;\n"
    "  padding-bottom: 2px;\n"
    "  margin: 0;\n"
    "}\n"
    "\n"
    "QMenuBar::item:selected {\n"
    "  color: palette(highlighted-text);\n"
    "  background: palette(highlight);\n"
    "}\n"
    "\n"
    "QMenu {\n"
    "  border: 1px solid #181818;\n"
    "}\n"
    "\n"
    "QHeaderView::section {\n"
    "  background: #303030;\n"
    "  border: 1px solid #181818;\n"
    "  border-top: 0;\n"
    "  margin-left: -1px;\n"
    "  padding-left: 4px;\n"
    "  padding-right: 4px;\n"
    "}\n"
    "\n"
    "QHeaderView::section:last {\n"
    "  margin-right: -1px;\n"
    "}\n"
    "\n"
    "QDockWidget\n"
    "{\n"
    "  titlebar-close-icon: url(\":/dark/dock-close.svg\");\n"
    "  titlebar-normal-icon: url(\":/dark/dock-undock.svg\");\n"
    "}\n";

class DarkStyle : public QProxyStyle
{
public:
    DarkStyle() : QProxyStyle("fusion") {}

    void polish(QApplication * app) override { QProxyStyle::polish(app); };
    void polish(QWidget * widget) override { QProxyStyle::polish(widget); }
    void polish(QPalette & palette) override;
};

void DarkStyle::polish(QPalette & palette)
{
    // normal colors
    // clang-format off
    palette.setColor(QPalette::WindowText,      QColor(0xf0, 0xf0, 0xf0));
    palette.setColor(QPalette::Button,          QColor(0x2c, 0x2c, 0x2c));
    palette.setColor(QPalette::Light,           QColor(0x70, 0x70, 0x70));
    palette.setColor(QPalette::Midlight,        QColor(0x60, 0x60, 0x60));
    palette.setColor(QPalette::Dark,            QColor(0x18, 0x18, 0x18));
    palette.setColor(QPalette::Mid,             QColor(0x50, 0x50, 0x50));
    palette.setColor(QPalette::Text,            QColor(0xf0, 0xf0, 0xf0));
    palette.setColor(QPalette::BrightText,      QColor(0xf0, 0xf0, 0xf0));
    palette.setColor(QPalette::ButtonText,      QColor(0xf0, 0xf0, 0xf0));
    palette.setColor(QPalette::Base,            QColor(0x20, 0x20, 0x20));
    palette.setColor(QPalette::Window,          QColor(0x38, 0x38, 0x38));
    palette.setColor(QPalette::Shadow,          QColor(0x00, 0x00, 0x00));
    palette.setColor(QPalette::Highlight,       QColor(0x15, 0x53, 0x9e)); // matches Adwaita-dark
    palette.setColor(QPalette::HighlightedText, QColor(0xff, 0xff, 0xff));
    palette.setColor(QPalette::Link,            QColor(0x20, 0x7e, 0xf0));
    palette.setColor(QPalette::LinkVisited,     QColor(0x20, 0x7e, 0xf0));
    palette.setColor(QPalette::AlternateBase,   QColor(0x28, 0x28, 0x28));
    palette.setColor(QPalette::ToolTipBase,     QColor(0x1d, 0x2c, 0x3f));
    palette.setColor(QPalette::ToolTipText,     QColor(0xf0, 0xf0, 0xf0));

    // disabled colors (where different from normal)
    palette.setColor(QPalette::Disabled, QPalette::WindowText,    QColor(0x80, 0x80, 0x80));
    palette.setColor(QPalette::Disabled, QPalette::Button,        QColor(0x34, 0x34, 0x34));
    palette.setColor(QPalette::Disabled, QPalette::Text,          QColor(0x80, 0x80, 0x80));
    palette.setColor(QPalette::Disabled, QPalette::BrightText,    QColor(0x80, 0x80, 0x80));
    palette.setColor(QPalette::Disabled, QPalette::ButtonText,    QColor(0x80, 0x80, 0x80));
    palette.setColor(QPalette::Disabled, QPalette::Base,          QColor(0x28, 0x28, 0x28));
    palette.setColor(QPalette::Disabled, QPalette::Link,          QColor(0x80, 0x80, 0x80));
    palette.setColor(QPalette::Disabled, QPalette::LinkVisited,   QColor(0x80, 0x80, 0x80));
    palette.setColor(QPalette::Disabled, QPalette::AlternateBase, QColor(0x30, 0x30, 0x30));
    // clang-format on
}

void enable_dark_theme()
{
    QApplication::setStyle(new DarkStyle());
    QString css = qApp->styleSheet();
    if (!css.contains(dark_css))
        qApp->setStyleSheet(dark_css + css);
}

void disable_dark_theme()
{
    QString css = qApp->styleSheet();
    qApp->setStyleSheet(css.replace(dark_css, ""));
    QApplication::setStyle(new QProxyStyle());
}

} // namespace audqt
