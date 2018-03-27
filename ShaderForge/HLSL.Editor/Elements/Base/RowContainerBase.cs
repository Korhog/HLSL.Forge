using System;
using Windows.UI;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Media;
using Windows.UI.Xaml.Controls;

namespace HLSL.Elements
{
    using rMind.Elements;
    using rMind.Content;

    /// <summary> Переопределенный контейнер </summary>
    public abstract class RowContainerBase : rMindRowContainer
    {
        public RowContainerBase(rMindBaseController parent) : base(parent)
        {
            AccentColor = Colors.DarkGray;
            BorderThickness = new Thickness(1);
            BorderRadius = new CornerRadius(3);
        }

        public override void Init()
        {
            base.Init();
            m_selector = new Border()
            {
                Margin = new Thickness(2),
                Background = new SolidColorBrush(Colors.Black),
                IsHitTestVisible = false,
                Visibility = Visibility.Collapsed
            };
        }
    }
}
