using System;
using Windows.UI;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Media;
using Windows.UI.Xaml.Controls;

namespace HLSL.Elements
{
    using rMind.Elements;
    using rMind.Content;
    using HLSL.Elements.Base;
    using HLSL.Values;

    public abstract class HeaderRowContainerBase : rMindHeaderRowContainer, IHLSLEditorNode
    {
        public HeaderRowContainerBase(rMindBaseController parent) : base(parent)
        {
            AccentColor = Colors.Black;
        }

        public virtual HLSLResult GetNodeValue(Node sender)
        {
            return null;
        }

        public override void Init()
        {
            base.Init();
            m_selector.Margin = new Thickness(-2);
            m_selector.Background = new SolidColorBrush(Colors.SkyBlue);
        }
    }

}
