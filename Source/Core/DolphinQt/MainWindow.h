// Copyright 2014 Dolphin Emulator Project
// Licensed under GPLv2
// Refer to the license.txt file included.

#pragma once

#include <memory>
#include <QMainWindow>

#include "Core/Core.h"

#include "DolphinQt/GameList/GameTracker.h"
#include "DolphinQt/VideoInterface/RenderWidget.h"

// Predefinitions
namespace Ui
{
class DMainWindow;
}

class DMainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit DMainWindow(QWidget* parent_widget = nullptr);
	~DMainWindow();

	// DRenderWidget
	bool RenderWidgetHasFocus() const { return m_render_widget->isActiveWindow(); }
	DRenderWidget* GetRenderWidget() { return m_render_widget.get(); }

signals:
	void CoreStateChanged(Core::EState state);

public slots:
	// Main toolbar (also used by DRenderWidget)
	bool OnStop();

private slots:
	// Emulation
	void StartGame(const QString filename);
	void OnCoreStateChanged(Core::EState state);

	// Main toolbar
	void OnOpen();
	void OnPlay();

	// View menu
	void OnGameListStyleChanged();

	// Help menu
	void OnOpenWebsite();
	void OnOpenDocs();
	void OnOpenGitHub();
	void OnOpenSystemInfo();
	void OnOpenAbout();

	// Misc.
	void UpdateIcons();

private:
	std::unique_ptr<Ui::DMainWindow> m_ui;
	DGameTracker* m_game_tracker;

	// Emulation
	QString RequestBootFilename();
	QString ShowFileDialog();
	void DoStartPause();

	std::unique_ptr<DRenderWidget> m_render_widget;
	bool m_isStopping = false;
};

// Pointer to the only instance of DMainWindow, used by Host_*
extern DMainWindow* g_main_window;
