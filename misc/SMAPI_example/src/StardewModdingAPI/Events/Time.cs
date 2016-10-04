using System;

namespace StardewModdingAPI.Events
{
    public static class TimeEvents
    {
        public static event EventHandler<EventArgsIntChanged> TimeOfDayChanged = delegate { };
        public static event EventHandler<EventArgsIntChanged> DayOfMonthChanged = delegate { };
        public static event EventHandler<EventArgsIntChanged> YearOfGameChanged = delegate { };
        public static event EventHandler<EventArgsStringChanged> SeasonOfYearChanged = delegate { };

        /// <summary>
        /// Occurs when Game1.newDay changes. True directly before saving, and False directly after.
        /// </summary>
        public static event EventHandler<EventArgsNewDay> OnNewDay = delegate { };

        internal static void InvokeTimeOfDayChanged(int priorInt, int newInt)
        {
            TimeOfDayChanged.Invoke(null, new EventArgsIntChanged(priorInt, newInt));
        }

        internal static void InvokeDayOfMonthChanged(int priorInt, int newInt)
        {
            DayOfMonthChanged.Invoke(null, new EventArgsIntChanged(priorInt, newInt));
        }

        internal static void InvokeYearOfGameChanged(int priorInt, int newInt)
        {
            YearOfGameChanged.Invoke(null, new EventArgsIntChanged(priorInt, newInt));
        }

        internal static void InvokeSeasonOfYearChanged(string priorString, string newString)
        {
            SeasonOfYearChanged.Invoke(null, new EventArgsStringChanged(priorString, newString));
        }

        internal static void InvokeOnNewDay(int priorInt, int newInt, bool newDay)
        {
            OnNewDay.Invoke(null, new EventArgsNewDay(priorInt, newInt, newDay));
        }
    }
}