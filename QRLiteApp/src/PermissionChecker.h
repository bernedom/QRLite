#pragma once

#include <QObject>
#include <QtCore/QDebug>
#include <qflags.h>

class QGuiApplication;

namespace QRLite {

class PermissionChecker : public QObject {
  Q_OBJECT
public:
  explicit PermissionChecker(QObject *parent = nullptr) : QObject(parent) {}

  Q_PROPERTY(bool cameraPermissionGranted READ cameraPermissionGranted WRITE
                 setCameraPermissionGranted NOTIFY cameraPermissionChanged)
  Q_PROPERTY(bool cameraCheckPending READ cameraCheckPending WRITE
                 setCameraCheckPending NOTIFY cameraCheckPendingChanged)

  void setCameraPermissionGranted(bool granted) {
    qDebug() << "Camera permission granted:" << granted;
    setCameraCheckPending(false);
    if (granted != _cameraPermissionGranted) {
      _cameraPermissionGranted = granted;
      emit cameraPermissionChanged(granted);
    }
  }

  void setCameraCheckPending(bool pending) {
    qDebug() << "Camera check pending:" << pending;
    if (pending != _cameraCheckPending) {
      _cameraCheckPending = pending;
      emit cameraCheckPendingChanged(pending);
    }
  }

  bool cameraPermissionGranted() const { return _cameraPermissionGranted; }
  bool cameraCheckPending() const { return _cameraCheckPending; }

signals:
  void cameraPermissionChanged(bool granted);
  void cameraCheckPendingChanged(bool pending);

private:
  bool _cameraPermissionGranted = false;
  bool _cameraCheckPending = true;
};
} // namespace QRLite