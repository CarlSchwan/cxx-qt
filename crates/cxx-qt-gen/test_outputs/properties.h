#pragma once

#include <memory>
#include <mutex>

namespace rust::cxxqtlib1 {
template<typename T>
class CxxQtThread;
}

namespace cxx_qt::my_object {
class MyObject;
using MyObjectCxxQtThread = ::rust::cxxqtlib1::CxxQtThread<MyObject>;
} // namespace cxx_qt::my_object

#include "cxx-qt-gen/ffi.cxx.h"

namespace cxx_qt::my_object {
class MyObject : public QObject
{
  Q_OBJECT
  Q_PROPERTY(::std::int32_t primitive READ getPrimitive WRITE setPrimitive
               NOTIFY primitiveChanged)
  Q_PROPERTY(
    QPoint trivial READ getTrivial WRITE setTrivial NOTIFY trivialChanged)
  Q_PROPERTY(Value opaque READ getOpaque WRITE setOpaque NOTIFY opaqueChanged)

public:
  explicit MyObject(QObject* parent = nullptr);
  ~MyObject();
  MyObjectRust const& unsafeRust() const;
  MyObjectRust& unsafeRustMut();
  ::std::unique_ptr<MyObjectCxxQtThread> qtThread() const;

public:
  ::std::int32_t const& getPrimitive() const;
  Q_SLOT void setPrimitive(::std::int32_t const& value);
  Q_SIGNAL void primitiveChanged();
  QPoint const& getTrivial() const;
  Q_SLOT void setTrivial(QPoint const& value);
  Q_SIGNAL void trivialChanged();
  Value const& getOpaque() const;
  Q_SLOT void setOpaque(Value const& value);
  Q_SIGNAL void opaqueChanged();

private:
  ::rust::Box<MyObjectRust> m_rustObj;
  ::std::shared_ptr<::std::recursive_mutex> m_rustObjMutex;
  ::std::shared_ptr<::rust::cxxqtlib1::CxxQtGuardedPointer<MyObject>>
    m_cxxQtThreadObj;
};

static_assert(::std::is_base_of<QObject, MyObject>::value,
              "MyObject must inherit from QObject");
} // namespace cxx_qt::my_object

namespace cxx_qt::my_object::cxx_qt_my_object {
::std::unique_ptr<MyObject>
newCppObject();
} // namespace cxx_qt::my_object::cxx_qt_my_object

Q_DECLARE_METATYPE(cxx_qt::my_object::MyObject*)
