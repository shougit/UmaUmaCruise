#pragma once
#pragma once

#include <unordered_set>
#include <wtl\atldlgs.h>
#include <wtl\atlddx.h>

#include "RaceDateLibrary.h"
#include "Config.h"

#include "Utility\json.hpp"
#include "DarkModeUI.h"

#include "resource.h"

class TrainingWindow :
	public CDialogImpl<TrainingWindow>,
	public CWinDataExchange<TrainingWindow>,
	public CCustomDraw<TrainingWindow>,
	public DarkModeUI<TrainingWindow>
{
public:
	enum { IDD = IDD_TRAINING };

	enum {
		kDockingMargin = 15
	};

	TrainingWindow(const Config& config) : m_config(config) {}

	void	ShowWindow(bool bShow);

	void	AnbigiousChangeCurrentTurn(const std::vector<std::wstring>& ambiguousCurrentTurn);

	void	EntryRaceDistance(int distance);

	void	ChangeIkuseiUmaMusume(const std::wstring& umaName);

	// overrides
	DWORD OnPrePaint(int /*idCtrl*/, LPNMCUSTOMDRAW /*lpNMCustomDraw*/);
	DWORD OnItemPrePaint(int /*idCtrl*/, LPNMCUSTOMDRAW /*lpNMCustomDraw*/);

	BEGIN_DDX_MAP(TrainingWindow)
		// Race
		DDX_TEXT(IDC_EDIT_NOWDATE, m_currentTurn)
	END_DDX_MAP()

	BEGIN_MSG_MAP_EX(TrainingWindow)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		MESSAGE_HANDLER(WM_DESTROY, OnDestroy)

		CHAIN_MSG_MAP(CCustomDraw<TrainingWindow>)
		CHAIN_MSG_MAP(DarkModeUI<TrainingWindow>)
		COMMAND_ID_HANDLER(IDCANCEL, OnCancel)

	END_MSG_MAP()

	LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnCancel(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);


	void OnExitSizeMove();


private:
	void _UpdateTraining(const std::wstring& turn);

	int32_t _GetRaceMatchState();
	void _SetRaceMatchState(int32_t state);

	void	_SwitchFavoriteRace(int index);
	bool	_IsFavoriteRaceTurn(const std::wstring& turn);

	enum RaceHighlightFlag {
		kAlter = 1 << 0,
		kFavorite = 1 << 1,
	};

	const Config& m_config;
	RaceDateLibrary	m_raceDateLibrary;

	CString	m_currentTurn;

	bool	m_showRaceAfterCurrentDate = true;

	bool	m_gradeG1 = true;
	bool	m_gradeG2 = true;
	bool	m_gradeG3 = true;

	bool	m_sprint = true;
	bool	m_mile = true;
	bool	m_middle = true;
	bool	m_long = true;

	bool	m_grass = true;
	bool	m_dart = true;

	bool	m_right = true;
	bool	m_left = true;
	bool	m_line = true;

	bool	m_raceLocation[RaceDateLibrary::Race::Location::kMaxLocationCount];

	CListViewCtrl	m_TrainingView;
	CEdit			m_editExpectURA;

	std::wstring	m_currentIkuseUmaMusume;
	nlohmann::json	m_jsonCharaFavoriteTraining;
	std::unordered_set<std::string>	m_currentFavoriteRaceList;

	enum ClassifyDistanceClass {
		kMinSprint = 1000, kMaxSprint = 1599,
		kMinMile = 1600, kMaxMile = 1999,
		kMinMiddle = 2000, kMaxMiddle = 2499,
		kMinLong = 2500, kMaxLong = 4000,
	};
	struct RaceDistanceData {
		int turn;
		int	distanceClass;

		RaceDistanceData(int turn, int distanceClass) : turn(turn), distanceClass(distanceClass) {}
	};
	std::vector<RaceDistanceData>	m_entryRaceDistanceList;

	struct ThemeColor {
		COLORREF	bkFavorite;
		COLORREF	bkRow1;
		COLORREF	bkRow2;
	};
	ThemeColor	m_darkTheme;
	ThemeColor	m_lightTheme;
};

