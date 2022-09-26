#include "cxx-qt-gen/include/my_object.cxxqt.h"

namespace cxx_qt::my_object {

MyObject::MyObject(QObject* parent)
  : QObject(parent)
  , m_rustObj(cxx_qt::my_object::cxx_qt_my_object::createRs())
  , m_rustObjMutex(std::make_shared<std::recursive_mutex>())
  , m_cxxQtThreadObj(
      std::make_shared<rust::cxxqtlib1::CxxQtGuardedPointer<MyObject>>(this))
{
}

MyObject::~MyObject()
{
  const auto guard = std::unique_lock(m_cxxQtThreadObj->mutex);
  m_cxxQtThreadObj->ptr = nullptr;
}

const MyObjectRust&
MyObject::unsafeRust() const
{
  return *m_rustObj;
}

MyObjectRust&
MyObject::unsafeRustMut()
{
  return *m_rustObj;
}

std::unique_ptr<MyObjectCxxQtThread>
MyObject::qtThread() const
{
  return std::make_unique<MyObjectCxxQtThread>(m_cxxQtThreadObj,
                                               m_rustObjMutex);
}

void
MyObject::invokable()
{
  const std::lock_guard<std::recursive_mutex> guard(*m_rustObjMutex);
  m_rustObj->invokableWrapper(*this);
}

void
MyObject::emitReady()
{
  const auto signalSuccess = QMetaObject::invokeMethod(
    this, [this]() mutable { Q_EMIT ready(); }, Qt::QueuedConnection);
  Q_ASSERT(signalSuccess);
}

void
MyObject::emitDataChanged(qint32 first,
                          ::std::unique_ptr<Opaque> second,
                          QPoint third)
{
  const auto signalSuccess = QMetaObject::invokeMethod(
    this,
    [this,
     first = std::move(first),
     second = std::move(second),
     third = std::move(third)]() mutable {
      Q_EMIT dataChanged(
        rust::cxxqtlib1::cxx_qt_convert<qint32, qint32>{}(std::move(first)),
        rust::cxxqtlib1::cxx_qt_convert<Value, ::std::unique_ptr<Opaque>>{}(
          std::move(second)),
        rust::cxxqtlib1::cxx_qt_convert<QPoint, QPoint>{}(std::move(third)));
    },
    Qt::QueuedConnection);
  Q_ASSERT(signalSuccess);
}

} // namespace cxx_qt::my_object

namespace cxx_qt::my_object::cxx_qt_my_object {
std::unique_ptr<MyObject>
newCppObject()
{
  return std::make_unique<MyObject>();
}
} // namespace cxx_qt::my_object::cxx_qt_my_object
