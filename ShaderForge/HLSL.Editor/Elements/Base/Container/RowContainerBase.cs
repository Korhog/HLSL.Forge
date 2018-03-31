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
            AccentColor = Colors.Black;
        }

        public override void Init()
        {
            base.Init();
            m_selector.Margin = new Thickness(-2);
            m_selector.Background = new SolidColorBrush(Colors.SkyBlue);
        }
    }
}
