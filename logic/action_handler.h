#ifndef ACTION_HANDLER_H
#define ACTION_HANDLER_H

#include <QObject>

class ActionHandler: public QObject {
  Q_OBJECT
public:
  explicit ActionHandler(QObject * parent);
  virtual ~ActionHandler();

public slots:
  void NewFile();
  void OpenFile();
};

#endif // ACTION_HANDLER_H
