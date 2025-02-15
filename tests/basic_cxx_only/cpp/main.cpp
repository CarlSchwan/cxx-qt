// clang-format off
// SPDX-FileCopyrightText: 2021 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
// clang-format on
// SPDX-FileContributor: Andrew Hayzen <andrew.hayzen@kdab.com>
// SPDX-FileContributor: Gerhard de Clercq <gerhard.declercq@kdab.com>
//
// SPDX-License-Identifier: MIT OR Apache-2.0
#include <QtTest/QTest>

#include "cxx-qt-gen/ffi.cxx.h"

int hidden_num = 100;

int
get_cpp_number()
{
  return hidden_num;
}

class CxxTest : public QObject
{
  Q_OBJECT

private Q_SLOTS:
  // Clean cxx allows basic interaction between C++ and Rust
  void test_cxx_interaction()
  {
    QCOMPARE(get_numbers_sum(), 102);
    hidden_num = 200;
    QCOMPARE(get_numbers_sum(), 202);
  }
};

QTEST_MAIN(CxxTest)
#include "main.moc"
