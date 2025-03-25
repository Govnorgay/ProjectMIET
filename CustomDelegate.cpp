#include "CustomDelegate.h"
#include <QLineEdit>
#include <QIntValidator>

CustomDelegate::CustomDelegate(QObject *parent) : QStyledItemDelegate(parent)
{
}

QWidget* CustomDelegate::createEditor(QWidget* parent,const QStyleOptionViewItem &option,const QModelIndex &index) const
{
    QLineEdit* editor = new QLineEdit(parent);
    QIntValidator* val = new QIntValidator(editor);
    val->setBottom(0);
    val->setRange(0, 99);
    editor->setValidator(val);
    if(editor->text().isEmpty())
        editor->setText("0");
    return editor;
}
